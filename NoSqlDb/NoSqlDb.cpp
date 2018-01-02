//////////////////////////////////////////////////////////////////////////////
//	NoSqlDb.cpp - key/value pair in-memory database							//
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
* This file- NoSqlDb.cpp comprises of demonstrating the functions for Add, Edit, Show and Delete
* by using NoSqlDb.h as it's header file for the function definitions
* 
* Public Methods:
* ==============
* main() - Demonstrating the functions of NoSqlDb Package 
*
* Required Files:
* ==============
* CppProperties:	CppProperties.h
* Convert:			Convert.h
*
* Maintenance History:
* ===================
* ver 1.0 : Feb 13, 2017 - first release
*/


#include "NoSqlDb.h"

using Key = NoSqlDb<StringData>::Key;
using Keys = NoSqlDb<StringData>::Keys; 

#ifdef NoSQl
int main()
{
	NoSqlDb<StringData>db;

	  /*
	  std::cout << "\n  size of db = " << db.count() << "\n";
	  Keys keys = db.keys();	// for printing the key values
	  for (Key key : keys)
	  {
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	  }
	  std::cout << "\n\n";

	  std::cout << "\n  Retrieving elements from NoSqlDb<IntData>";
	  std::cout << "\n ---------------------------------------\n";

	  std::cout << "\n  size of idb = " << idb.count() << "\n";
	  Keys ikeys = idb.keys();
	  for (Key key : ikeys)
	  {
		std::cout << "\n  " << key << ":";
		std::cout << idb.value(key).show();
	  }
	  std::cout << "\n\n";
	  */

	  //////////////////////////////////////Adding String Elements start here//////////////////////////////////////////////////////////////////////////////
	std::cout << "\n  Creating and saving NoSqlDb elements with String data";
	std::cout << "\n -------------------------------------------------------\n";

	Element<StringData> element1;						//Create String Data Element 1 of the NoSql database
	element1.itemName = "element1";
	element1.category = "test1";
	element1.textDesc = "Parent of element3 and element4";
	element1.timeDate = "Fri-Feb-03-2017 13:01";
	element1.childVector = { "element3", "element4" };
	element1.data = "element1's StringData";

	db.save(element1.itemName, element1);		//function call to store the values of String Data Element 1 in the DB
	//db.value("1").show();

	Element<StringData> element2;								//Create String Data Element 2 of the NoSql database
	element2.itemName = "element2";
	element2.category = "test2";
	element2.textDesc = "Child of element4";					//no Child Vector for this element
	element2.timeDate = "Sat-Feb-04-2017 19:50";
	element2.data = "element2's StringData";

	db.save(element2.itemName, element2);

	Element<StringData> element3;
	element3.itemName = "element3";
	element3.category = "test1";
	element3.textDesc = "Child of element1";					//no Child Vector for this element
	element3.timeDate = "Sun-Feb-05-2017 05:20";
	element3.data = "element3's StringData";

	db.save(element3.itemName, element3);

	Element<StringData> element4;
	element4.itemName = "element4";
	element4.category = "test2";
	element4.textDesc = "Child of element1, Parent of element2";
	element4.timeDate = "Mon-Feb-06-2017 13:01";
	element4.childVector = { "element2" };
	element4.data = "element4's StringData";

	db.save(element4.itemName, element4);

	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "\n  String data successfully saved in the String Database-db!";
	//////////////////////////////////////Adding String Elements ends here//////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////Adding Int Elements start here//////////////////////////////////////////////////////////////////////////////
	std::cout << "\n  Creating and saving NoSqlDb elements with Integer data";
	std::cout << "\n ----------------------------------------------------\n";

	NoSqlDb<IntData> idb;

	Element<IntData> ielement1;								//Create String Data Element 1 of the NoSql database

	ielement1.itemName = "element1";
	ielement1.category = "test1";
	ielement1.textDesc = "Parent of element3 and element4";
	ielement1.timeDate = "Fri-Feb-03-2017 13:01";
	ielement1.childVector = { "element3", "element4" };
	ielement1.data = 1;

	idb.save(ielement1.itemName, ielement1);					//function call to store the values of String Data Element 1 in the DB

	Element<IntData> ielement2;								//Create String Data Element 2 of the NoSql database
	ielement2.itemName = "element2";
	ielement2.category = "test2";
	ielement2.textDesc = "Child of element4";					//no Child Vector for this element
	ielement2.timeDate = "Sat-Feb-04-2017 19:50";
	ielement2.data = 2;

	idb.save(ielement2.itemName, ielement2);

	Element<IntData> ielement3;
	ielement3.itemName = "element3";
	ielement3.category = "test1";
	ielement3.textDesc = "Child of element1";					//no Child Vector for this element
	ielement3.timeDate = "Sun-Feb-05-2017 05:20";
	ielement3.data = 3;

	idb.save(ielement3.itemName, ielement3);

	Element<IntData> ielement4;
	ielement4.itemName = "element4";
	ielement4.category = "test2";
	ielement4.textDesc = "Child of element1, Parent of element2";
	ielement4.timeDate = "Mon-Feb-06-2017 13:01";
	ielement4.childVector = { "element2" };
	ielement4.data = 4;

	idb.save(ielement4.itemName, ielement4);

	std::cout << "\n ----------------------------------------------------\n";
	std::cout << "\n  Integer data successfully saved in the database- idb!";
	//////////////////////////////////////Adding Int Elements ends here//////////////////////////////////////////////////////////////////////////////

  ///////////////////////// to Print a vector element//////////////////////////////////////////////////////////////////////////////////
  //std::cout << "\n\n Printing a vector element: ";
  //Element<StringData> printElem = element1;
  //db.printVector(printElem, db); // the argument in the .h file should be <Data> we don't have to change there
  /////////////////////////to Print a vector element//////////////////////////////////////////////////////////////////////////////

  /////////////////////////// write a func for editing the keys ///////////////////////////////////////////////////////////////////
  ///// why are key and element both needed to be passed as an argument? one should be fine!!
  //std::cout << "\n\n Editing a key: ";
  //Key editKey = "3";
  //Element<StringData> editElem = element4;
  //db.editElement(editKey, editElem);
  /////////////////////////////////////// write func should end here //////////////////////////////////////////////////////////////

  ///////////////////////// to delete a vector element//////////////////////////////////////////////////////////////////////////////
  std::cout << "\n\n Deleting a key: ";
  Key delKey = "3";
  db.deleteElement(delKey);

  std::cout << "\n\n Trying to print the element which we deleted now : ";
  std::cout << "\n  " << delKey << " : ";										//delKey holds the Name value of the Element
  std::cout << "Call to .value(key).show() : " << db.value(delKey).show();
  /////////////////////////to delete a vector element/////////////////////////////////////////////////////////////////////////////

  //////////////////////////////// delete a Parent as well as it's Child element /////////////////////////////////////////////////
  //std::cout << "\n\n Deleting a Parent as well as it's Child element: ";
  //Key delParentnChild= "3";
  //db.deleteParent_wChild(delParentnChild);
  //////////////////////////////// delete a Parent as well as it's Child element /////////////////////////////////////////////////

  std::cout << "\n\n";
  system("pause");
}

#endif // !NoSqlMain 
