//////////////////////////////////////////////////////////////////////////////
//	Test.cpp - key/value pair in-memory database							//
//																			//
//	ver 1.0																	//
//	Language:		Visual C++ 2011, Visual Studio 2015 Community Edition	//
//	Platform:		HP Envy x360, Core i7, Windows 10 Home					//
//	Application:	CSE 687 Project #1, Spring 2017							//
//	Author:			Amritbani Sondhi,										//
//					Graduate Student, Syracuse University					//
//					asondhi@syr.edu											//
//	Source:			Jim Fawcett, CST 4-187, Syracuse University				//
//					(315) 443-3948, jfawcett@twcny.rr.com					//
//////////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * ==================
 * The package uses the NoSqlDb package to perform the Add, Edit, Show and Delete
 * functions on the Elements by using an object of a String or Integer Database
 * This file- Test.cpp performs 
 * It covers the Part 3 function definitions of Project #1, Spring 2017
 *
 * Public Methods:
 * ==============
 * toXml() : Retrieving values from the Database to an XML file
 * fromXml() : Retrieving values from an XML file to the Database
 * main() : Demonstrating the functions of NoSqlDb Package and Project1 package
 *
 * Required Files:
 * ==============
 * NoSqlDb:			NoSqlDb.h
 * XmlDocument:	XMLDocument.h, XmlElement.h
 * 
 * Maintenance History:
 * ===================
 * ver 1.0 : Feb 13, 2017 - first release
 */

#include "../NoSqlDb/NoSqlDb.h"
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"

using ElemStrData= Element<StringData>;
using namespace XmlProcessing;
using SPtr = std::shared_ptr<AbstractXmlElement>;
using VecPtr = std::vector<SPtr>;
using Key = NoSqlDb<StringData>::Key;
using Keys = NoSqlDb<StringData>::Keys;

///////////////////////// PART 3: PERSISTING DATA TO AND FROM AN XML FILE ////////////////////////////
// Retrieving values from the Database to an XML file
StringData toXml(NoSqlDb<StringData> stringDatabaseObj)
{
	StringData xml;
	XmlDocument doc;

	SPtr pRoot = makeTaggedElement("stringDbObj");				// Creating the main root element
	doc.docElement() = pRoot;

	Keys keys = stringDatabaseObj.keys();
	for (Key key : keys)										// Loop for adding all the Element child nodes
	{															// to the main Root
		SPtr pRoot1 = makeTaggedElement("element");
		pRoot->addChild(pRoot1);

		// make Property<string> itemName element and add to root
		SPtr pItemName = makeTaggedElement("itemName");
		pRoot1->addChild(pItemName);							// All metadata should refer to the Root of element
		SPtr pTextElem = makeTextElement(stringDatabaseObj.value(key).itemName);
		pItemName->addChild(pTextElem);

		// make Property<string> category element and add to root
		SPtr pCategory = makeTaggedElement("category");
		pRoot1->addChild(pCategory);							// All metadata should refer to the Root of element
		pTextElem = makeTextElement(stringDatabaseObj.value(key).category);
		pCategory->addChild(pTextElem);

		// make Property<string> textDesc element and add to root
		SPtr pTextDesc = makeTaggedElement("textDesc");
		pRoot1->addChild(pTextDesc);
		pTextElem = makeTextElement(stringDatabaseObj.value(key).textDesc);
		pTextDesc->addChild(pTextElem);

		// make Property<string> timeDate element and add to root
		SPtr pTimeDate = makeTaggedElement("timeDate");
		pRoot1->addChild(pTimeDate);
		pTextElem = makeTextElement(stringDatabaseObj.value(key).timeDate);
		pTimeDate->addChild(pTextElem);

		// make Property<string> childVector element and add to root
		SPtr pChildVector = makeTaggedElement("childVector");
		pRoot1->addChild(pChildVector);

		// Loop for Adding the Sub-Nodes of the Child Elements
		VectorInst vector = stringDatabaseObj.value(key).childVector;
		for (ChildVector::iterator i = vector.begin();  i != vector.end(); i++ )
		{
			// make Property<string> childkey element and add to Child Vector Root
			SPtr pChildTagElement = makeTaggedElement("childkey");
			pChildVector->addChild(pChildTagElement);
			SPtr pChildTextElem = makeTextElement(*i);
			pChildTagElement->addChild(pChildTextElem);
		}

		// make Property<string> data element and add to root
		SPtr pData = makeTaggedElement("data");
		pRoot1->addChild(pData);
		pTextElem = makeTextElement(stringDatabaseObj.value(key).data);
		pData->addChild(pTextElem);
	}
	xml = doc.toString();				// xml String will be used to transfer the data from DB to the file
	return xml;
}

// Retrieving values from an XML file to the Database
NoSqlDb<StringData> fromXml(const StringData &docPath)
{
	NoSqlDb<StringData> db;
	try
	{
		XmlDocument doc(docPath, XmlDocument::file);
		VecPtr desc = doc.descendents("element").select();		// Retrieving data from XML element

		int size = desc.size();
		for (int i = 0; i < size; i++)				// Loop for retrieving metadata from element tag
		{
			Element<StringData> elem;

			VecPtr desc = doc.descendents("itemName").select();
			StringData tagValue = desc[i]->children()[0]->value();
			elem.itemName = tagValue;

			desc = doc.descendents("category").select();
			tagValue = desc[i]->children()[0]->value();
			elem.category = tagValue;

			desc = doc.descendents("textDesc").select();
			tagValue = desc[i]->children()[0]->value();
			elem.textDesc = tagValue;

			desc = doc.descendents("timeDate").select();
			tagValue = desc[i]->children()[0]->value();
			elem.timeDate = tagValue;

			desc = doc.descendents("data").select();
			tagValue = desc[i]->children()[0]->value();
			elem.data = tagValue;

			VecPtr desc2 = doc.descendents("childVector").select()[i]->children();
			int size1 = desc2.size();
			for (int j = 0; j < size1; j++)
			{
				StringData vecTagValue = desc2[j]->children()[0]->value();
				elem.childVector.getValue().push_back(vecTagValue);
			}
			db.save(elem.itemName, elem);
		}
	}
	catch (std::exception& ex)
	{
		std::cout << "\n  something bad happened";
		std::cout << "\n  " << ex.what();
	}
	return db;
}

int main()
{
	// Initializing objects to the Database
	NoSqlDb<StringData> stringDbObj;
	NoSqlDb<IntData> intDbObj;

	//////////////////////////// PART 1: ADD, EDIT AND DELETE FROM THE DB ///////////////////////
	// ADD //
	stringDbObj = stringDbObj.addStringDataElements();
	intDbObj = intDbObj.addIntDataElements();

	// EDIT //
	Key editStringKey = "element3";						// Element who's key is to be edited 	
	Element<StringData> editElement;					// Create a new element which is to be edited
	editElement = stringDbObj.value(editStringKey);		// Copy the value of the orginal element in the new one
	editElement.category = "Changed the text desc through editStringElement()"; // Reflecting the change
	std::cout << "\n -------------------------------------------------------";
	stringDbObj.editElement(editStringKey, editElement);
	std::cout << "\n After Editing, " << editStringKey << " is: " << std::endl;
	std::cout << stringDbObj.value(editStringKey).show();
	std::cout << "\n -------------------------------------------------------";
	
	// DELETE //
	Key deleteStringKey = "element4";					// Element which is to be deleted
	stringDbObj.deleteElement(deleteStringKey);

	std::cout << "\n Printing the whole DB again: " << std::endl;
	Keys keys = stringDbObj.keys();
	for (Key key : keys)
	{
		std::cout << "\n " << key << " : ";
		std::cout << stringDbObj.value(key).show();
	}
	std::cout << "\n -------------------------------------------------------";

	///////////////////////////////// PART 2: QUERYING NOSQL DB /////////////////////////////////////
	std::vector<ElemStrData> stringVec;

	StringData searchItem = "element2";
	stringVec = stringDbObj.searchItemName(searchItem);
	std::cout << "\n Searching " << searchItem << " by using Search Item Name Query: " << std::endl;
	for (ElemStrData e : stringVec)				// For printing the values of all the resultant Elements
		std::cout << e.show();
	std::cout << "\n -------------------------------------------------------";

	StringData searchCat = "test1";
	stringVec = stringDbObj.searchCategory(searchCat);
	std::cout << "\n Searching Category - " << searchCat << " by using Search Category Query: " << std::endl;
	for (ElemStrData e : stringVec)				// For printing the values of all the resultant Elements
		std::cout << e.show();
	std::cout << "\n -------------------------------------------------------";

	StringData searchTextDesc = "Child of element4";
	stringVec = stringDbObj.searchTextDesc(searchTextDesc);
	std::cout << "\n Searching Text Desc - " << searchTextDesc << " by using Search Text Desc Query: " << std::endl;
	for (ElemStrData e : stringVec)				// For printing the values of all the resultant Elements
		std::cout << e.show();
	std::cout << "\n -------------------------------------------------------";
	
	///////////////////////// PART 3: PERSISTING DATA TO AND FROM AN XML FILE ////////////////////////////
	StringData path = "../Project_XML_Document.xml";					// The Location of your File

	// TO XML DOCUMENT //
	StringData xmlStringTo;
	std::ofstream myfile;						// An object for creating the XML file
	myfile.open(path);
	xmlStringTo = toXml(stringDbObj);
	myfile << xmlStringTo;						// Passing the String Data from DB to the file
	myfile.close();
	
	// FROM XML DOCUMENT //
	stringDbObj = fromXml(path);				// DB object in which data is retrieved from the file
	std::cout << "\n Printing the whole DB again after the execution of xml: " << std::endl;
	keys = stringDbObj.keys();
	for (Key key : keys)
	{
		std::cout << "\n " << key << " : ";
		std::cout << stringDbObj.value(key).show();
	}
	std::cout << "\n -------------------------------------------------------";

	system("pause");
}

