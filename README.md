# Word_Catalog.h<br>
#### A header file for making a word catalog from a textbook.Able to deal with the wchar.
## class Word_Catalog<br>
* data member (private)<br>
**string fileName** a filename for catalog file , default form txt<br>
**vector\<wstring> words** wstring vector for words in catalog <br><br>
* constructor (public)<br>
**Word_Catalog(std::string & bookName,size_t wordamout = wordAmount)** default **wordAmount** 3000 <br>
**Word_Catalog(size_t wordamout = wordAmount)** default **fileName** "unamed_wordCatalog.txt"<br><br>
* member function (public)<br>
**void writeCatalog()** creat catalog file with **fileName** <br>
**void writeCatalog(std::string &selfName)** creat catalog file with **selfName**<br>
**void printCatalog()** print **Word_Catalog.words** to screen<br><br>
* non-member function (friend)<br>
**std::wifstream& operator>>** read **Word_Catalog.words** from wifstream to **Word_Catalog**<br>
**std::wifstream& operator<<** write **Word_Catalog.words** from **Word_Catalog** to wofstream<br><br>
* non-member function (non-friend)<br>
**void youhua(std::vector<std::wstring> &wwords)** processing include **removepunc/toLower/sort/finalcheck**<br>
---
# mainchar.cpp
#### A source cpp file for making a word catalog from a textbook.Only able to deal with the char.<br>

---
**Lastest update time:** 2018-8-13 12:21:11 <br>
**Author:** Alan Redsheep
