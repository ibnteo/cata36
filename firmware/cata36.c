/*
 * Project: Chord keyboard CatBoard-A36
 * Version: 0.1
 * Date: 2019-08-09
 * Author: Vladimir Romanovich <ibnteo@gmail.com>
 * License: MIT
 * https://github.com/ibnteo/catboarda36
 */

#include "Descriptors.h"
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/power.h>
#include <avr/wdt.h>

void Ports_Init(void);
void LED_On(void);
void LED_Off(void);
void LED_Toggle(void);
void LED_Switch(bool);
void LED2_On(void);
void LED2_Off(void);
void LED2_Toggle(void);
void LED2_Switch(bool);

void Keyboard_Scan(void);
void Settings_Read(void);
void Settings_Write(void);
void Layout_Switch(void);
void Hardware_Setup(void);

uint16_t Chords[8] = {0, 0, 0, 0, 0, 0, 0, 0};
// Ports_Init(), LEDs(), Keyboard_Scan()
#include "catboard2.h"
//#include "ergodox.h"
//#include "jian.h"

// Layers
//#include "qwerty.h"
//#include "qwerty2.h"
#include "jcuken2.h"

#define LAYER1 0
#define LAYER2 1

#define NAV_MODE 0
#define MOU_MODE 1

#define MACROS_BUFFER_SIZE 70
#define MACROS_BUFFER_MAX 10
uint8_t Macros_Buffer[MACROS_BUFFER_SIZE];
uint8_t Macros_Index = 0;

int16_t Mouse_X;
int16_t Mouse_Y;
int16_t Mouse_W;
uint8_t Mouse_Button;
uint8_t Mouse_Button_Click;

const int16_t mouMoves[16] PROGMEM = {20, 1,   5,   10,  15,  30,  40,  50,
                                      75, 100, 200, 300, 400, 500, 750, 1000};
const int16_t mouScrolls[16] PROGMEM = {10, 1,  2,  4,  7,  15, 20, 25,
                                        30, 40, 50, 60, 70, 80, 90, 100};

bool Chord_Growing = true;
uint8_t Q_Mods = 0;
uint8_t Q_Multiplier = 0;
uint8_t Q_Nav = NAV_MODE;
uint8_t Layer_Current = LAYER1;

uint16_t Chords_Last[8] = {0, 0, 0, 0, 0, 0, 0, 0};

// EEPROM Settings
#define LAYOUTS_TWO 0
#define LAYOUTS_ONE 1

uint8_t Layout_Mode = LAYOUTS_TWO;
uint8_t EE_Layout_Mode EEMEM;

#define OS_LINUX 0
#define OS_WINDOWS 1
#define OS_MAC 2
#define OS_ANDROID 3

uint8_t OS_Mode = OS_LINUX;
uint8_t EE_OS_Mode EEMEM;

uint8_t Meta = HID_KEYBOARD_MODIFIER_LEFTCTRL;

void Settings_Read() {
  Layout_Mode = eeprom_read_byte(&EE_Layout_Mode);
  OS_Mode = eeprom_read_byte(&EE_OS_Mode);
  Meta = (OS_Mode == OS_MAC) ? HID_KEYBOARD_MODIFIER_LEFTGUI
                             : HID_KEYBOARD_MODIFIER_LEFTCTRL;
}
void Settings_Write() {
  eeprom_write_byte(&EE_Layout_Mode, Layout_Mode);
  eeprom_write_byte(&EE_OS_Mode, OS_Mode);
}

void Layout_Switch() {
  if (OS_Mode == OS_WINDOWS) { // Ctrl+Shift
    Macros_Buffer[Macros_Index++] = 0;
    Macros_Buffer[Macros_Index++] =
        HID_KEYBOARD_MODIFIER_LEFTSHIFT | HID_KEYBOARD_MODIFIER_LEFTCTRL;
  } else if (OS_Mode == OS_MAC ||
             OS_Mode == OS_ANDROID) { // Cmd+Space || Win+Space
    Macros_Buffer[Macros_Index++] = HID_KEYBOARD_SC_SPACE;
    Macros_Buffer[Macros_Index++] = HID_KEYBOARD_MODIFIER_LEFTGUI;
  } else { // Alt+Shift
    Macros_Buffer[Macros_Index++] = 0;
    Macros_Buffer[Macros_Index++] =
        HID_KEYBOARD_MODIFIER_LEFTSHIFT | HID_KEYBOARD_MODIFIER_LEFTALT;
  }
}

/** Buffer to hold the previously generated Keyboard HID report, for comparison
 * purposes inside the HID class driver. */
static uint8_t PrevKeyboardHIDReportBuffer[sizeof(USB_KeyboardReport_Data_t)];

/** Buffer to hold the previously generated Mouse HID report, for comparison
 * purposes inside the HID class driver. */
static uint8_t PrevMouseHIDReportBuffer[sizeof(USB_MouseReport_Data_t)];

/** LUFA HID Class driver interface configuration and state information. This
 * structure is passed to all HID Class driver functions, so that multiple
 * instances of the same class within a device can be differentiated from one
 * another. This is for the keyboard HID interface within the device.
 */
USB_ClassInfo_HID_Device_t Keyboard_HID_Interface = {
    .Config =
        {
            .InterfaceNumber = 0,
            .ReportINEndpoint =
                {
                    .Address = KEYBOARD_IN_EPADDR,
                    .Size = HID_EPSIZE,
                    .Banks = 1,
                },
            .PrevReportINBuffer = PrevKeyboardHIDReportBuffer,
            .PrevReportINBufferSize = sizeof(PrevKeyboardHIDReportBuffer),
        },
};

/** LUFA HID Class driver interface configuration and state information. This
 * structure is passed to all HID Class driver functions, so that multiple
 * instances of the same class within a device can be differentiated from one
 * another. This is for the mouse HID interface within the device.
 */
USB_ClassInfo_HID_Device_t Mouse_HID_Interface = {
    .Config =
        {
            .InterfaceNumber = 1,
            .ReportINEndpoint =
                {
                    .Address = MOUSE_IN_EPADDR,
                    .Size = HID_EPSIZE,
                    .Banks = 1,
                },
            .PrevReportINBuffer = PrevMouseHIDReportBuffer,
            .PrevReportINBufferSize = sizeof(PrevMouseHIDReportBuffer),
        },
};

/** Configures the board hardware and chip peripherals for the demo's
 * functionality. */
void Hardware_Setup() {
  // Set for 16 MHz clock
  // CLKPR = 0x80; CLKPR = 0;

  /* Disable watchdog if enabled by bootloader/fuses */
  MCUSR &= ~(1 << WDRF);
  wdt_disable();

  /* Disable clock division */
  clock_prescale_set(clock_div_1);

  Ports_Init();
  LED_On();
  USB_Init();
  LED_Off();
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void) {
  // LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void) {
  // LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void) {
  bool ConfigSuccess = true;

  ConfigSuccess &= HID_Device_ConfigureEndpoints(&Keyboard_HID_Interface);
  ConfigSuccess &= HID_Device_ConfigureEndpoints(&Mouse_HID_Interface);

  USB_Device_EnableSOFEvents();

  // LED_Switch(! ConfigSuccess);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void) {
  HID_Device_ProcessControlRequest(&Keyboard_HID_Interface);
  HID_Device_ProcessControlRequest(&Mouse_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void) {
  HID_Device_MillisecondElapsed(&Keyboard_HID_Interface);
  HID_Device_MillisecondElapsed(&Mouse_HID_Interface);
}

/** HID class driver callback function for the creation of HID reports to the
 * host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface
 * configuration structure being referenced \param[in,out] ReportID    Report ID
 * requested by the host if non-zero, otherwise callback should set to the
 * generated report ID \param[in]     ReportType  Type of the report to create,
 * either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature \param[out] ReportData
 * Pointer to a buffer where the created report should be stored \param[out]
 * ReportSize  Number of bytes written in the report (or zero if no report is to
 * be sent)
 *
 *  \return Boolean true to force the sending of the report, false to let the
 * library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(
    USB_ClassInfo_HID_Device_t *const HIDInterfaceInfo, uint8_t *const ReportID,
    const uint8_t ReportType, void *ReportData, uint16_t *const ReportSize) {
  if (Macros_Index < (MACROS_BUFFER_SIZE - MACROS_BUFFER_MAX)) {

    uint16_t chords[8] = {Chords[0], Chords[1], Chords[2], Chords[3],
                          Chords[4], Chords[5], Chords[6], Chords[7]};
    Keyboard_Scan();

    bool isRelease = Chords[0] < chords[0] || Chords[1] < chords[1] ||
                     Chords[2] < chords[2] || Chords[3] < chords[3] ||
                     Chords[4] < chords[4] || Chords[5] < chords[5] ||
                     Chords[6] < chords[6] || Chords[7] < chords[7];
    bool isPress = Chords[0] > chords[0] || Chords[1] > chords[1] ||
                   Chords[2] > chords[2] || Chords[3] > chords[3] ||
                   Chords[4] > chords[4] || Chords[5] > chords[5] ||
                   Chords[6] > chords[6] || Chords[7] > chords[7];

    if (isPress) {
      Chord_Growing = true;
    } else if (isRelease) {
      if (Chord_Growing) {

        uint8_t layer = Layer_Current;
        if (isRelease) {
          Chords_Last[0] = chords[0];
          Chords_Last[1] = chords[1];
        }
        Chord_Growing = false;

        if (Layer_Current != layer) {
          Layout_Switch();
        }
      }
    }
  }
  /* Determine which interface must have its report generated */
  if (HIDInterfaceInfo == &Keyboard_HID_Interface) {
    USB_KeyboardReport_Data_t *KeyboardReport =
        (USB_KeyboardReport_Data_t *)ReportData;

    if (Macros_Index) {
      KeyboardReport->KeyCode[0] =
          (Macros_Buffer[0] == 0xFF ? 0 : Macros_Buffer[0]);
      KeyboardReport->Modifier = Macros_Buffer[1];
      if (Macros_Buffer[0] == Macros_Buffer[2] && Macros_Buffer[2] != 0xFF) {
        Macros_Buffer[0] = 0xFF;
      } else {
        for (uint8_t i = 0; i <= (Macros_Index - 2); i += 2) {
          Macros_Buffer[i + 0] = Macros_Buffer[i + 2];
          Macros_Buffer[i + 1] = Macros_Buffer[i + 3];
          if (!Macros_Buffer[i + 0] && !Macros_Buffer[i + 1])
            break;
        }
        Macros_Buffer[MACROS_BUFFER_SIZE - 1] = 0;
        Macros_Buffer[MACROS_BUFFER_SIZE - 2] = 0;
        Macros_Index -= 2;
      }
    } else {
      KeyboardReport->Modifier = Q_Mods;
    }
    LED2_Switch(KeyboardReport->Modifier);

    *ReportSize = sizeof(USB_KeyboardReport_Data_t);
    return true;
  } else {
    USB_MouseReport_Data_t *MouseReport = (USB_MouseReport_Data_t *)ReportData;

    int8_t mouseX = Mouse_X > 100 ? 100 : (Mouse_X < -100 ? -100 : Mouse_X);
    if (Mouse_X > 100)
      Mouse_X -= 100;
    else if (Mouse_X < -100)
      Mouse_X += 100;
    else
      Mouse_X = 0;

    int8_t mouseY = Mouse_Y > 100 ? 100 : (Mouse_Y < -100 ? -100 : Mouse_Y);
    if (Mouse_Y > 100)
      Mouse_Y -= 100;
    else if (Mouse_Y < -100)
      Mouse_Y += 100;
    else
      Mouse_Y = 0;

    int8_t mouseW = Mouse_W > 100 ? 100 : (Mouse_W < -100 ? -100 : Mouse_W);
    if (Mouse_W > 100)
      Mouse_W -= 100;
    else if (Mouse_W < -100)
      Mouse_W += 100;
    else
      Mouse_W = 0;

    MouseReport->X = mouseX;
    MouseReport->Y = mouseY;
    MouseReport->W = mouseW;

    MouseReport->Button = Mouse_Button | Mouse_Button_Click;
    if (!Mouse_X && !Mouse_Y && !Mouse_W)
      Mouse_Button_Click = 0;

    *ReportSize = sizeof(USB_MouseReport_Data_t);
    return true;
  }
}

/** HID class driver callback function for the processing of HID reports from
 * the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface
 * configuration structure being referenced \param[in] ReportID    Report ID of
 * the received report from the host \param[in] ReportType  The type of report
 * that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has
 * been stored \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(
    USB_ClassInfo_HID_Device_t *const HIDInterfaceInfo, const uint8_t ReportID,
    const uint8_t ReportType, const void *ReportData,
    const uint16_t ReportSize) {
  if (HIDInterfaceInfo == &Keyboard_HID_Interface) {
    uint8_t *LEDReport = (uint8_t *)ReportData;

    if (*LEDReport & HID_KEYBOARD_LED_CAPSLOCK) {
      // LED_On();
    }

    if (*LEDReport & HID_KEYBOARD_LED_SCROLLLOCK) {
      // LED_On();
    }

    /*uint8_t  LEDMask   = LEDS_NO_LEDS;

    if (*LEDReport & HID_KEYBOARD_LED_NUMLOCK)
      LEDMask |= LEDS_LED1;

    LEDs_SetAllLEDs(LEDMask);*/
  }
}

int main(void) {
  Hardware_Setup();
  GlobalInterruptEnable();
  Settings_Read();
  while (true) {
    HID_Device_USBTask(&Keyboard_HID_Interface);
    HID_Device_USBTask(&Mouse_HID_Interface);
    USB_USBTask();
  }
}
