# Word_Catalog.h<br>
#### A header file for making a word catalog from a textbook.Able to deal with the wchar.
## class Word_Catalog<br>
* data member (private)<br>
1.**string fileName**<br> a filename for catalog file , default form txt<br>
2.**vector\<wstring> words**<br> wstring vector for words in catalog <br><br>
* constructor (public)<br>
1.**Word_Catalog(std::string & bookName,size_t wordamout = wordAmount)**<br> default **wordAmount** 3000 <br>
2.**Word_Catalog(size_t wordamout = wordAmount)**<br> default **fileName** "unamed_wordCatalog.txt"<br><br>
* member function (public)<br>
1.**void writeCatalog()**<br> creat catalog file with **fileName** <br>
2.**void writeCatalog(std::string &selfName)**<br> creat catalog file with **selfName**<br>
3.**void printCatalog()**<br> print **words** to screen<br><br>
* non-member function (friend)<br>
1.**std::wifstream& operator>>**<br> read **words** from wifstream to **Word_Catalog**<br>
2.**std::wifstream& operator<<**<br> write **words** from **Word_Catalog** to wofstream<br><br>
* non-member function (non-friend)<br>
1.**void youhua(std::vector<std::wstring> &wwords)**<br> processing include **removepunc/toLower/sort/finalcheck**<br>
---
# mainchar.cpp
#### A source cpp file for making a word catalog from a textbook.An old version only able to deal with the char.<br>
---
**Lastest update time:** 2018-8-13 12:21:11 <br>
**Author:** Alan Redsheep
