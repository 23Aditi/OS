#!/bin/bash

#display
display(){
	echo "List of files is (in cwd):"
	ls -1
}

#test if a file exists
isExisting(){
	echo "Enter the name of file :"
	read file_name
	if [[ -f "$file_name" ]]; then
		echo "File found!"
	else
		echo "File not found!"
	fi
}

#read a file
readFile(){
	echo "Enter name of file"
	read file_name
	if [[ -f "$file_name" ]]; then
		cat "$file_name"
	else
		echo "file doesn't exists!"
	fi
}
#delete a file!
delete(){
	echo "Enter the name of file"
	read file_name
	if [[ -f "$file_name" ]]; then
		rm "$file_name"
		echo "File deleted successfully!"
	else
		echo "file doesn't exists!"
	fi
}

#menu
echo -e "Press : \n1)Test if file exists\n2)read a file \n3)delete a file \n4) display a file\n"
read choice
case $choice in
	1) isExisting;;
	2) readFile;;
	3) delete;;
	4) display;;
	*) echo "Invalid input"
esac
