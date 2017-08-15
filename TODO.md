# DataGUI - TODO


#### Requirements

- File formats to exchange data with the core app:
	- **JSON** (pros: universal, simple, structured, efficient; cons: ). http://www.json.org/
	- `XML`  (pros: universal, structured; cons: inefficient, verbose). http://en.wikipedia.org/wiki/XML_data_binding  
	- `YAML` (pros: JSON superset; cons: not as spread). http://en.wikipedia.org/wiki/YAML
	- `Plain text format` (pros: simple; cons: unstructured).
	- `Google Protocol Buffers`: ?

- Allow to use a ram disk, a hard disk or a remote device to store data.  
    In UNIX this is completely transparent.
- Optionally use other IPC methods (ref.: http://en.wikipedia.org/wiki/Interprocess_communication).
- Optionally use a database.

- For each parameter, show the date of the last change.

- Allow to visualize data in different formats (e.g. trees, tables, lists, plots, ...).
	- Automatically group data items in tree branches/tables/tabs/... according to their nesting in the input data structure.
	  Doing so the appearance of the data can be implicitly determined by the input file structure.

- Allow to save/load snapshots of the current values.

- Move the data that changed since the previous transfer only.
	- Use a file to store the whole data, and one to store the deltas.
	- At the beginning all the available data will be sent.
	- With the following iterations, just move what changed.
	- If a new tag is sent, add it.
	- If an existing tag is sent, update its corresponding value and date.
	- This point has less priority in case the RAM disk is used.

- Two usage modes:
	- Viewer.
	- Viewer and setter (a subset of the parameters may be modifiable).

- Considerations
    - Some of these functionalities are typical of:
		- Spreadsheets:
		 	- Cons: not optimized for partial data changes; no tree structure.
		- Databases:
		    - Pros:
				- SQLite can be a good tool.
			    - Advanced interaction (possibility to view/modify multiple parameters at once).
			    - Nothing to do, apart from the DB itself.
			- Cons: overkill for this task. Or maybe not?


- Log user operations (different purposes: diagnostic, automated sets of operations, ...)

- Options to send back the new values:
    - For each value modified by the user, as soon as the change takes place.
	- For a bunch of changes, when the user presses the [commit]/[send]/[update]/... button.


#### Implementation:

- QT
    - Use a QTreeView, not a QTreeWidget
	    - The tree and the data are separated. More flexibility.
		- Different representation of the same data.
		- ParamGUI2, DataGUI

- HTML5
	- Pros: can run on a mobile phone.
	- https://github.com/jdorn/json-editor

#### Customization

- Load details about the core application to display in the corresponding dialog and on the title bar.
	- Load an icon to show on the GUI (useful to differentiate multiple GUIs for different apps).

#### Bugs

    - Cannot commit the icons in git; gitignore is fine [?].

#### References

	http://doc.qt.io/qt-5/examples-itemviews.html
	http://doc.qt.io/qt-5/qtwidgets-itemviews-simpletreemodel-example.html
	http://doc.qt.io/qt-5/qtwidgets-itemviews-editabletreemodel-example.html
	http://doc.qt.io/qt-5/qjsondocument.html
	http://doc.qt.io/qt-5/qtwidgets-itemviews-simplewidgetmapper-example.html
	http://doc.qt.io/qt-5/qtwidgets-itemviews-combowidgetmapper-example.html
	http://doc.qt.io/qt-5/qtwidgets-itemviews-chart-example.html


#### Licenses

	Icons:
		<div>Icons made by <a href="http://www.freepik.com" title="Freepik">Freepik</a> from <a href="http://www.flaticon.com" title="Flaticon">www.flaticon.com</a> is licensed by <a href="http://creativecommons.org/licenses/by/3.0/" title="Creative Commons BY 3.0" target="_blank">CC 3.0 BY</a></div>
