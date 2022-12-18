
#Documentation ​📚
### ❔ &middot; How we use eeprom in the project ? 🔍
#### Like this !  ✅​📝
###### Start the connection
```cpp
EEPROM.begin(512);
```
###### Clear the memory 
```cpp
for (int i = 0; i < 96; ++i)
		{
          EEPROM.write(i, 0);
        }
```
###### Write the SSID in the memory
```cpp

String qsid = "ssid";
for (int i = 0; i < qsid.length(); ++i)
        {
          EEPROM.write(i, qsid[i]);
          Serial.println(qsid[i]);
        }
```
###### Write the Password in the memory
```cpp
String qpass = "password";
        for (int i = 0; i < qpass.length(); ++i)
        {
          EEPROM.write(32 + i, qpass[i]);
          Serial.print("Wrote: ");
          Serial.println(qpass[i]);
        }
```
###### Commit all the change of the EEPROM
```cpp
EEPROM.commit();
```
###### Read the SSID from the memory
```cpp
  String esid;
  for (int i = 0; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));
  }
```
###### Read the password from the memory
```cpp
String epass = "";
  for (int i = 32; i < 96; ++i)
  {
    epass += char(EEPROM.read(i));
  }
```
