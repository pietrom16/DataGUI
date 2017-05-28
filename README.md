# DataGUI

Simple dialog to view (and modify) data generated by another application.

### TODO

- Priority 1:
	- Load a JSON file with tags/comments/ranges/...
	- Load/save a JSON file with tags/values.
	- Check consistency between the two JSON files.
	- Build an internal QTreeView as a merge of both JSON files: Tag/value/comment/range.

- Priority 2:
	- Check values are in range, in DataGUI, as soon as entered.
	- Check values are in range, on the server.
	- Highlight and font size for tags/values on the basis of:
		- Time when last changed by the user.
		- Time when last changed by the server.
		- Below/above specified limits.
		- Continuous colour related to value.
		- Importance specified by the user.
		- Importance specified by the server.
		- Set the features of a parent equal to the highest features of its leafs.
	- Notation:
		- Time → background spectrum colours.
		- Red: above limit; Blue: below limit.
		- Value → foreground spectrum colours.
		- Font size: importance.

- Priority 3:
	- Add a logger.
	- Allow to save the expansion status of the tree. With a complex parameter hierarchy, it can be useful to have what need readily available. Load it by default.
	- Record the values in time, and show a small plot.
	- Allow to load/save from a database.
	- Consider the YAML format.


### References
https://github.com/nlohmann/json
