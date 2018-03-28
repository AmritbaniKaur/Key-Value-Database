
Key/Value Database project:
---------------------------

Req 1 : Implemented in C++ using the facilities of the standard C++ Libraries and Visual Studio 2015

Req 2 : Implemented a template class providing key/value in-memory databases where each value consists of:
	. Metadata:
		- An item name string
		- A category name string
		- A text description of the item
		- A time-date string recording the date and time the value was written to the database.
		- a finite number (possibly zero) of child relationships with other values. Each element of the child relationships collection 
			is the key of another item in the database. Any item holding a key in this collection is the parent of the element accessed 
			by the key.
	. An instance of the template type1. This might be a string, a container of a set of values of the same type, or some other 
		collection of data captured in some, perhaps custom, data structure.

Req 3 : supports addition and deletion of key/value pairs.

Req 4 : supports editing of values including the addition and/or deletion of relationships, editing text metadata, and replacing an existing 
	value's instance with a new instance. Editing of keys is forbidden.

Req 5 : on command, persists database contents to an XML file. This process be reversible, e.g., the database can be restored or augmented 
	from an existing XML file as well as write its contents out to an XML file.

Req 6 : accepts a positive time interval or number of writes after which the database contents are persisted. This scheduled "save" 
	process shall continue until cancelled. By default, timed saving is turned off.

Req 7 : supports queries for:
	. The value of a specified key.
	. The children of a specified key.
	. The set of all keys matching a specified pattern which defaults to all keys.
	. All keys that contain a specified string in their item name
	. All keys that contain a specified string in their category name
	. All keys that contain a specified string in their template data section when that makes sense.
	. All keys that contain values written within a specified time-date interval. If only one end of the interval is provided shall take 
		the present as the other end of the interval.
	. Each query accepts a list of keys4 and returns a collection of keys from the list that match the query.

Req 8 : supports making the same kinds of queries, cited in the requirement above, on the set of keys returned by an earlier query.

Req 9 : supports forming a union of the keys from two or more earlier queries.

Req 10: submitted with contents, in the form of an XML file, that describes the project's package structure and dependency 
	relationships that can be loaded when the project is graded.

Req 11: accompanied by a test executive that clearly demonstrates all the functional requirements #2-#9, above. 
	The XML file supplied in the previous requirement will be used as part of that demonstration.

----------------------------------------------------------------------------------
