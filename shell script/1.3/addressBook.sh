#!/bin/bash


# empid;name;address
file_name="addressBook.txt"
if [[ ! -f "$file_name" ]]; then
	touch "$file_name"
	echo "Empid;Name;Address" >> "$file_name"
fi

#display
display(){
	if [[ -f "$file_name" ]]; then
		echo "Content of address book is :"
		cat "$file_name"
	else
		echo "File doesn't exists!"
	fi
}
#insert
insert(){
	if [[ -f "$file_name" ]]; then
		echo "enter empid"
		read empid
		echo "enter name"
		read name
		echo "enter address"
		read address
		echo "$empid;$name;$address" >> "$file_name"
		echo "Record inserted successfully!"
	else
		echo "file doesn't exists!"
	fi
}

#remove
delete(){
	if [[ -f "$file_name" ]]; then
		echo "enter empid"
		read empid
		if grep -q "^$empid;" "$file_name"; then
			grep -v "^$empid;" "$file_name" > temp.txt && mv temp.txt "$file_name"
			echo "Record deleted successfully!"
		else
			echo "Record not found"
		fi
	else
		echo "file not found!"
	fi
}

#edit
edit(){
	if [[ -f "$file_name" ]]; then
		echo "enter empid"
		read empid
		if grep -q "^$empid;" "$file_name"; then
			echo "enter new name"
			read name
			echo "enter new address"
			read address
			grep -v "^$empid;" "$file_name" > temp.txt && mv temp.txt "$file_name"
			echo "$empid;$name;$address" >> "$file_name"
			echo "Record modified successfully!!"
		else
			echo "Record not found!!"
		fi
	else
		echo "file not found"
	fi
}
search(){
	if [[ -f "$file_name" ]]; then
		echo "Enter the empid:"
		read empid
		if grep -q "^$empid;" "$file_name"; then
			echo "Record found!!!"
			grep "^$empid;" "$file_name"
		else
			echo "Record not found!!"
		fi
	else
		echo "File not found!"
	fi
}

#menu
echo -e "Press :\n1)search \n2)insert \n3)remove \n4)edit \n5)display"
read choice

case $choice in
	1) search;;
	2) insert;;
	3) delete;;
	4) edit;;
	5) display ;;
	*) echo "Invalid Input!";;
esac
