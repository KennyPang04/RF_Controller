# RadioFrequency Controller
RadioFrequency Controller will be an embedded device capable of detecting, receiving, storing, and transmitting RF signals. The project focuses on developing low-level firmware, signal processing, and reliable communication devices.

## About the Project!
### Current Progress
- Developing drivers for I2C and EEPROM, to learn how to format and develop drivers for any device.
- Implementing error-correcting codes to learn how to develop firmware that store data in safe methods.
- Configure RF signals into simple data types for persistent RF storage.

### Planned Features
- Integrating a screen using SPI for user interface.
- Build a matrix keypad for the user interface.
- Construct a PC application communicating with the microcontroller with UART. 
- The PC application will be a reader that reads all EEPROM data and allows the users to see a waveform of the stored RF signal.
- Adding signal processing & filtering to reduce noise.
- Adding real applications like a scheduled RF transmission.
- Using FreeRTOS on the Tiva for task management.

## Datasheets Referenced
- **Tiva TM4C123GH6PM Microcontroller** - [Datasheet Link](https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf?ts=1782663824098&ref_url=https://www.ti.com/product/TM4C123GH6PM%253Futm_source=google&utm_medium=cpc&utm_campaign=epd-tech-inno-dynpf_mcuproc-cpc-pf-google-eu_en_int&utm_content=prodfolddynamic&ds_k=DYNAMIC+SEARCH+ADS&dcm=yes&gclsrc=aw.ds&gad_source=1&gad_campaignid=23830055180&gbraid=0AAAAAC068F2O39gx82943UaGDPpCEn1Kk)
- **24LC512 IC EEPROM** - [Datasheet Link](https://ww1.microchip.com/downloads/aemDocuments/documents/MPD/ProductDocuments/DataSheets/24AA512-24LC512-24FC512-512-Kbit-I2C-Serial-EEPROM-DS20001754.pdf)

### Future Usage Datasheets
- https://mm.digikey.com/Volume0/opasdata/d220001/medias/docus/5773/CN0295D%20other%20related%20document.pdf
- https://www.ti.com/lit/an/spma085/spma085.pdf?ts=1782006630682

## Running this project
1. Clone the repository.