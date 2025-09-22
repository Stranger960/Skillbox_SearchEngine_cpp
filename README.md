# Skillbox diploma project: SearchEngine     <img width="60" height="82" alt="image" src="https://github.com/user-attachments/assets/62431dec-ee86-49aa-947a-01e9da8f1ddf" />

This project is the final part of the *C++ training course* provided by **Skillbox** ( www.skillbox.ru ).
It is implementing a search engine *console* program for a company corporate portal, like Google search - 
based on the *data relevance* evaluation. 
It builds *search indexes*, works with configuration files and invokes a set of tests to validate the solution.  
A *relevance formula* for generating search results is used as the project basis.  
Project was developed in the MS Visual Studio environment. 



## *** Project structure  
*SearchEngine* is the main project module.  
3 classes are implemented:
- *ConverterJSON* involves methods responsible for *config.json* and *requests.json* files reading  
and for writing processing results to *answres.json*.  

- *InvertedIndex* class uses data from text blocks (originally located in resources folder)
and builds an inverted index from them. An inverted index is a data structure in which,
for each word in a collection of documents, the corresponding list contains all documents
in the collection where that word occurs.
Data are stored in *map<string, vector<Entry>> freqDictionary*, where *Entry* is constructed as follows:
*struct Entry { size_t docId, count; }*  
*InvertedIndex* data are then used for text quick search.  

- *SearchServer*  ...  


Input file *config.json* describes the configuration, including source data files used for search:  
<img width="324" height="323" alt="image" src="https://github.com/user-attachments/assets/db358f19-3914-406b-bfc3-b68086a92a0b" />  


Input file *requests.json* includes the list of keywords used for search, where each line represents  
one single search request:  
<img width="383" height="222" alt="image" src="https://github.com/user-attachments/assets/77f561af-a964-4d93-b8f9-8330cd59022b" />  


  
Project structure in MS VS is as follows:
<p>
<img width="232" height="446" alt="image" src="https://github.com/user-attachments/assets/67a9762f-a4b6-48b8-9335-1e7384ba96c1" />
</p>

##  *** Stack of technologies used
<p>
</p>

## *** Features
Key benefits:
<p>
</p>

## *** Running program locally  
Result interpretation  
  <p>
    <img width="213" height="301" alt="image" src="https://github.com/user-attachments/assets/1ac0e25b-cfe2-44ec-a90f-e652eec9bacb" />
  </p>

## *** Replacing project
...
<p>
</p>

## *** Configuration / команды, действия, переменные среды, которые обязательно требуется задать
...
<p>
</p>


## *** Errata
...
<p>
</p>



## *** Contributing
...
<p>
</p>

### *** Licenses
nlohmann/json: MIT  
GoogleTest: BSD-3-Clause  
Project code: MIT © 2025 Grach Muradyan
