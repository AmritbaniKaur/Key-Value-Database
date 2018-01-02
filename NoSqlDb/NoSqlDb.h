#pragma once
//////////////////////////////////////////////////////////////////////////////
//	NoSqlDb.h - key/value pair in-memory database							//
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
 * The package creates a No SQL Database for String and/ or Integer Data values 
 * This file- NoSqlDb.h comprises of all the functions for Add, Edit, Show and Delete
 * and also, queries for searching the database with metadata values like itemName,
 * category and text description.
 * It covers the Part 1 and Part 2 function definitions of Project #1, Spring 2017
 * 
 * Public Methods:
 * ==============
 * Element Class : represents a data record in our NoSql database through Properties
 *	- Defines all the properties for getting and setting the values of the metadata of Elements
 *	- show() : Displaying all the Metadata and Data of the Element
 *
 * NoSqlDb Class : is a key/value pair in-memory database, stores and retrieves the elements
 *	- keys() : Pushing Data into the Vector
 *	- save() : Saving the element into the database
 *	- value() : Getting the Element's Data from a Key
 * 	- count() : Getting the size of the Unordered Map
 *	- addStringDataElements() : Adding Elements to the String DB
 *	- addIntDataElements() : Adding Elements to the Integer DB
 *	- editElement() : Edit Elements of the DB
 * 	- deleteElement() : Delete Elements of the DB
 *	- searchItemName() : Search by ItemName of the Element
 * 	- searchCategory() : Search by Category of the Element
 *	- searchTextDesc() : Search by Text Description of the Element
 *
 * Required Files:
 * ==============
 * CppProperties:	CppProperties.h
 * Convert:			Convert.h
 *
 * Build Process:
 * ==============
 * NoSqlDb:			NoSqlDb.cpp
 * 
 * Maintenance History:
 * ===================
 * ver 1.0 : Feb 13, 2017 - first release
 */

#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include "../CppProperties/CppProperties.h"
#include "../Convert/Convert.h"

using ItemName = std::string;
using Category = std::string;
using TextDesc = std::string;
using ChildVector = std::vector<std::string>;
using TimeDate = std::string;
using StringData = std::string;
using IntData = int;
using VectorInst = std::vector<StringData>;

/////////////////////////////////////////////////////////////////////
// Element class represents a data record in our NoSql database
//
template<typename Data>
class Element
{
public:
  Property<ItemName> itemName;			// metadata
  Property<Category> category;			// metadata
  Property<TextDesc> textDesc;			// metadata
  Property<ChildVector> childVector;	// metadata
  Property<TimeDate> timeDate;			// metadata
  Property<Data> data;					// data

  StringData show();
};

// Displaying all the Metadata and Data of the Element
template<typename Data>
StringData Element<Data>::show()
{
  std::ostringstream out;
  out.setf(std::ios::adjustfield, std::ios::left);
  out << "\n    " << std::setw(8) << "Item Name" << " : " << itemName;
  out << "\n    " << std::setw(8) << "Category" << " : " << category;
  out << "\n    " << std::setw(8) << "TextDesc" << " : " << textDesc;
  out << "\n    " << std::setw(8) << "TimeDate" << " : " << timeDate;

  // Loop for displaying the Child Vectors of the element
  for (int i = 0; i < childVector.getValue().size(); i++)   
  {
	 out << "\n    " << std::setw(8) << "Child Vector" << " : " << childVector.getValue()[i];
  }

  out << "\n    " << std::setw(8) << "Data" << " : " << data;

  out << "\n";
  return out.str();
}

/////////////////////////////////////////////////////////////////////
// NoSqlDb class is a key/value pair in-memory database
// - stores and retrieves elements
//
template<typename Data>
class NoSqlDb
{
public:
	using Key = std::string;
	using Keys = std::vector<Key>;

	Keys keys();
	bool save(Key key, Element<Data> elem);
	Element<Data> value(Key key);
	size_t count();

	NoSqlDb<StringData> addStringDataElements();
	NoSqlDb<IntData> addIntDataElements();

	Element<Data> editElement(Key key, Element<Data>);
	Element<Data> deleteElement(Key key);

	std::vector<Element<Data>> searchItemName(Key itemName);
	std::vector<Element<Data>> searchCategory(Key category);
	std::vector<Element<Data>> searchTextDesc(Key textDesc);

private:
	using Item = std::pair<Key, Element<Data>>;
	// To store the key and the values in an unordered map
	std::unordered_map<Key, Element<Data>> store; 
};

// Pushing Data into the Vector
template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::keys()
{
  Keys keys;
  for (Item item : store)
  {
    keys.push_back(item.first);
  }
  return keys;
}

// Save the element into the database
template<typename Data>
bool NoSqlDb<Data>::save(Key key, Element<Data> elem)
{
  if(store.find(key) != store.end())			// If element is present
    return false;
  store[key] = elem;							// If not; Save
  return true;
}

// Get the Element's Data from a Key
template<typename Data>
Element<Data> NoSqlDb<Data>::value(Key key)
{
  if (store.find(key) != store.end())
    return store[key];
  return Element<Data>();
}

// Get the size of the Unordered Map
template<typename Data>
size_t NoSqlDb<Data>::count()
{
	return store.size();
}

//////////////////////////// PART 1: ADD, EDIT AND DELETE FROM THE DB //////////////////////////////
// Adding Elements to the String DB
template<typename Data>
NoSqlDb<StringData> NoSqlDb<Data>::addStringDataElements()
{
	NoSqlDb<StringData> stringDatabaseObj;
	std::cout << "\n -------------------------------------------------------";
	std::cout << "\n Creating and saving NoSqlDb elements with String data";

	Element<StringData> element1;				//Create String Data Element 1 of the NoSql database
	element1.itemName = "element1";
	element1.category = "test1";
	element1.textDesc = "Parent of element3 and element4";
	element1.timeDate = "Fri-Feb-03-2017 13:01";
	element1.childVector = { "element3", "element4" };
	element1.data = "element1's StringData";

	stringDatabaseObj.save(element1.itemName, element1);		//store the values of String Data Element 1 in the DB

	Element<StringData> element2;				//Create String Data Element 2 of the NoSql database
	element2.itemName = "element2";
	element2.category = "test2";
	element2.textDesc = "Child of element4";	//no Child Vector for this element
	element2.timeDate = "Sat-Feb-04-2017 19:50";
	element2.data = "element2's StringData";

	stringDatabaseObj.save(element2.itemName, element2);

	Element<StringData> element3;
	element3.itemName = "element3";
	element3.category = "test1";
	element3.textDesc = "Child of element1";	//no Child Vector for this element
	element3.timeDate = "Sun-Feb-05-2017 05:20";
	element3.data = "element3's StringData";

	stringDatabaseObj.save(element3.itemName, element3);

	Element<StringData> element4;
	element4.itemName = "element4";
	element4.category = "test2";
	element4.textDesc = "Child of element1, Parent of element2";
	element4.timeDate = "Mon-Feb-06-2017 13:01";
	element4.childVector = { "element2" };
	element4.data = "element4's StringData";

	stringDatabaseObj.save(element4.itemName, element4);

	std::cout << "\n  String data successfully saved in the String Database";
	std::cout << "\n -------------------------------------------------------";

	// Printing the String Database of all the Elements
	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "\n  The String Database of all the Elements: ";

	Keys keys = stringDatabaseObj.keys();
	for (Key key : keys)
	{
		std::cout << "\n " << key << ":";
		std::cout << stringDatabaseObj.value(key).show();
	}
	std::cout << "\n -------------------------------------------------------\n";

	return stringDatabaseObj;
}

// Adding Elements to the Integer DB
template<typename Data>
NoSqlDb<IntData> NoSqlDb<Data>::addIntDataElements()
{
	NoSqlDb<IntData> intDatabaseObj;

	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "\n  Creating and saving NoSqlDb elements with Integer data";

	Element<IntData> ielement1;					//Create String Data Element 1 of the NoSql database

	ielement1.itemName = "element1";
	ielement1.category = "test1";
	ielement1.textDesc = "Parent of element3 and element4";
	ielement1.timeDate = "Fri-Feb-03-2017 13:01";
	ielement1.childVector = { "element3", "element4" };
	ielement1.data = 1;

	intDatabaseObj.save(ielement1.itemName, ielement1);	//function call to store the values of String Data Element 1 in the DB

	Element<IntData> ielement2;					//Create String Data Element 2 of the NoSql database
	ielement2.itemName = "element2";
	ielement2.category = "test2";
	ielement2.textDesc = "Child of element4";	//no Child Vector for this element
	ielement2.timeDate = "Sat-Feb-04-2017 19:50";
	ielement2.data = 2;

	intDatabaseObj.save(ielement2.itemName, ielement2);

	Element<IntData> ielement3;
	ielement3.itemName = "element3";
	ielement3.category = "test1";
	ielement3.textDesc = "Child of element1";	//no Child Vector for this element
	ielement3.timeDate = "Sun-Feb-05-2017 05:20";
	ielement3.data = 3;

	intDatabaseObj.save(ielement3.itemName, ielement3);

	Element<IntData> ielement4;
	ielement4.itemName = "element4";
	ielement4.category = "test2";
	ielement4.textDesc = "Child of element1, Parent of element2";
	ielement4.timeDate = "Mon-Feb-06-2017 13:01";
	ielement4.childVector = { "element2" };
	ielement4.data = 4;

	intDatabaseObj.save(ielement4.itemName, ielement4);

	std::cout << "\n  Integer data successfully saved in the Integer Database";
	std::cout << "\n -------------------------------------------------------\n";

	// Printing the Integer Database of all the Elements
	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "\n  The Integer Database of all the Elements: ";

	Keys keys = intDatabaseObj.keys();
	for (Key key : keys)
	{
		std::cout << "\n " << key << ":";
		std::cout << intDatabaseObj.value(key).show();
	}

	std::cout << "\n -------------------------------------------------------\n";

	return intDatabaseObj;
}

// Edit Elements of the DB
template<typename Data>
Element<Data> NoSqlDb<Data>::editElement(Key key, Element<Data> element)
{
	store[key] = element;
	std::cout << "\n\n " << key << " is edited successfully " << std::endl;
	return Element<Data>();
}

// Delete Elements of the DB
template<typename Data>
Element<Data> NoSqlDb<Data>::deleteElement(Key key) //deletes the key value pair
{
	if (store.find(key) != store.end())
		store.erase(key);
	std::cout << "\n The Element with " << key << " key is successfully deleted from the Database";

	return Element<Data>();
}

///////////////////////////////////////// PART 2: QUERYING /////////////////////////////////////////
// Search by ItemName of the Element
template<typename Data>
std::vector<Element<Data>> NoSqlDb<Data>::searchItemName(Key itemName)
{
	std::vector<Element<Data>> vector;
	for (Item i : store) 
	{
		if (Convert<Property<StringData>>::toString(i.second.itemName) == itemName)
		{
			vector.push_back(i.second);
		}
	}
	return vector;
}

// Search by Category of the Element
template<typename Data>
std::vector<Element<Data>> NoSqlDb<Data>::searchCategory(Key category)
{
	std::vector<Element<Data>> vector;
	for (Item i : store) {
		if (Convert<Property<StringData>>::toString(i.second.category) == category) {
			vector.push_back(i.second);
		}
	}
	return vector;
}

// Search by Text Description of the Element
template<typename Data>
std::vector<Element<Data>> NoSqlDb<Data>::searchTextDesc(Key textDesc)
{
	std::vector<Element<Data>> vector;
	for (Item i : store) {
		if (Convert<Property<StringData>>::toString(i.second.textDesc) == textDesc) {
			vector.push_back(i.second);
		}
	}
	return vector;
}
