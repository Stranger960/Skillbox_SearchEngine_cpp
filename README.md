# Skillbox diploma project: SearchEngine  <img width="60" height="82" alt="image" src="https://github.com/user-attachments/assets/62431dec-ee86-49aa-947a-01e9da8f1ddf" />

This project is the final part of the *C++ training course* provided by **Skillbox** ( www.skillbox.ru ).
It is implementing a search engine *console* program for a company corporate portal, like Google search - 
based on the *data relevance* evaluation. 
It builds *search indexes*, works with configuration files and invokes a set of tests to validate the solution.  
A *relevance formula* (from the project task file above) for generating search results was used as the calculations basis.  


## *** Project structure  
Project structure in MS VS is as follows:
<p>
<img width="232" height="446" alt="image" src="https://github.com/user-attachments/assets/67a9762f-a4b6-48b8-9335-1e7384ba96c1" />
</p>

*Search_engine* is the main project module.  

3 classes are implemented:
- *ConverterJSON* class involves methods responsible for *config.json* and *requests.json* files reading  
and for writing processing results to *answres.json*.  

- *InvertedIndex* class methods use data from text blocks (originally located in resources folder)
and build an inverted index from them. An inverted index is a data structure where,
for each word in a collection of documents, the corresponding list contains all documents
in the collection where that word occurs.
After processing data are then stored in a map *freqDictionary* and are used later for text quick searches.  

- *SearchServer* class includes methods, which allow to determine the most relevant documents
matching given search query based on the list of search queries from the *requests.json* file. 


Input file *config.json* describes the configuration, including source data files used for search.  
Each data file ("document") contains no more than 1000 words, with a maximum length of 100 characters per word.  
The words consist of lowercase Latin letters and are separated by one or more spaces,   
max-responses field limits max number of responses per one singe request:  
<img width="324" height="323" alt="image" src="https://github.com/user-attachments/assets/db358f19-3914-406b-bfc3-b68086a92a0b" />  


Input file *requests.json* includes the list of keywords used for search, where each line represents  
one single search request (words separated by one or more spaces of lowercase Latin letters).  
Up to 1K request lines where each line is 1 to 10 words:  
<img width="383" height="222" alt="image" src="https://github.com/user-attachments/assets/77f561af-a964-4d93-b8f9-8330cd59022b" />  


##  *** Stack of technologies used  
This is a local and pure backend solution, developed on C++.  
Unit tests, based on GoogleTest, are included for code control.


## *** Features
Key benefits: project design is targeted to provide maximum flexibility,  
where user can easily work with own datasets:  
- add or modify the documents to be analyzed (within *config.json* file)  
- adapt the keywords used for search (inside *requests.json* file).


## *** Running program locally  
...

## *** Results interpretation  
For each request (line from the input file *requests.json*) program returns in the output *answers.json* file one block with the relevance array.  
Each array element shows the relevance (*rank*) for the given *docid*  (document number – from the list of files in *config.json*):  
<p>
    <img width="290" height="400" alt="image" src="https://github.com/user-attachments/assets/faafe31e-1cda-4c7a-8f6f-b61690782cdc" />
</p>


## *** Project configuration and replication
Project was developed using Microsoft *Visual Studio* Community 2022.  
Following requirements should be mentioned:  
•	Compiler C++17 and higher versions  
•	CMake 3.20 and higher versions  
•	Internet access could be needed (for loading in advance or at the time of linking) for the remote entities used,
including *GoogleTest* and *nlohmann/jsonn* library.  
Project could be easily replicated / cloned either using GitHub Fork option or by creating a corresponding structure and code copy / past in any available IDE.

## *** Errata  
Following item from the Task file was noted during the development  
(https://github.com/Stranger960/Skillbox_SearchEngine_cpp/blob/master/Final%20project%20task%20for%20C%2B%2B%20Skillbox%20training%20course.pdf):
the output *answers.json* file must have a unique key ( "docid" ) per each record.  
Also couple of corrections / comments were added to unit test (TestCaseInvertedIndex, TestBasic2):  
<img width="500" height="305" alt="image" src="https://github.com/user-attachments/assets/2be20973-8228-40b1-af9b-8d716a46a3c7" />  


## *** Contributing  
**Special thanks** to *Michael Verbkin* and the whole hard-working Skillbox team for the permanent support during the training course  
and at the final project development time.  

## *** Licenses
nlohmann/json: MIT  
GoogleTest: BSD-3-Clause  
Project code: MIT © 2025 Grach Muradyan
