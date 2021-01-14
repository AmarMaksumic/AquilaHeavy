// include the SD library:
#include <SPI.h>
#include <SD.h>

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
// MKRZero SD: SDCARD_SS_PIN
// VELLEMAN I/O VMA304: SD shield: pin 10 

bool initialize_card(int card_pin) {
  if (!card.init(SPI_HALF_SPEED, card_pin) && !volume.init(card)) {
  return false;
  } else {
  return true;
  }
}

String read_file(int card_pin, String file_name) {
  File file;
  String contents = "";
  SD.begin(card_pin);

  file = SD.open(file_name);
  if (file) {
    while (file.available()) {
      contents += file.read();
    }
    file.close();
  }

  return contents;
}

bool write_file(int card_pin, String file_name, String content) {
  File file;
  SD.begin(card_pin);

  file = SD.open(file_name, FILE_WRITE);

  if (file) {
    file.println(content);
    file.close();
    return true;
  } else {
    return false;
  }
}

String card_type() {
  switch (card.type()) {
  case SD_CARD_TYPE_SD1:
      return "SD1";
  case SD_CARD_TYPE_SD2:
      return "SD2";
  case SD_CARD_TYPE_SDHC:
      return "SDHC";
  default:
      return "N/a";
  }
}