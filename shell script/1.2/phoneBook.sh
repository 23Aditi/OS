#!/bin/bash

file_name="Phone Book.txt"

if [[ ! -f "$file_name" ]]; then
	touch "$file_name"
	echo -e "Name\tPhoneNumber" >> "$file_name"
fi

#insert
insert(){
	if [[ -f "$file_name" ]]; then
		echo "enter name"
		read name
		echo "enter phone no"
		read phoneNo
		echo -e "$name\t$phoneNo" >> "$file_name"
		echo "Record entered successfully!"
	else
		echo "file doesn't exist!"
	fi
}

#display
display(){
	echo "Enter name or phone no"
	read input
	if grep -i -q "$input" "$file_name"; then
		echo "Record found!!"
		grep -i "$input" "$file_name"
	else
		echo "Record not found!!"
	fi
}

#sort
sorting(){
	sort -t ' ' -k2,2 "$file_name" -o "$file_name"
	echo "Record sorted successfully!"
}

#delete 
delete(){
	echo "Enter the name or phone no"
	read input
	if grep -i -q "$input" "$file_name"; then
		grep -v "$input" "$file_name" > temp.txt && mv temp.txt "$file_name"
		echo "Record deleted successfully!"
	else
		echo "Record not found!"
	fi
}

#menu
echo -e "Press :\n1)Insert record \n2)display match \n3)sorting \n4)delete an entry"
read choice
case $choice in
	1) insert;;
	2) display;;
	3) sorting;;
	4) delete;;
	*) echo "Invalid choice!!";;
esac


