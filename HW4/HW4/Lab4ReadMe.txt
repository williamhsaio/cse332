{\rtf1\ansi\ansicpg1252\cocoartf1504\cocoasubrtf830
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 Compilation Problems\
\
Issues compelling the instance function:\
	-Error LNK2019: Unresolved External Symbol in Visual Studio [duplicate]\
	-To fix this complication error I had to go back and make sure that the function returned a 	scoped GameBase::game instead of just game.\
\
Saving the Game:\
	-When saving the game there were issue with formatting the displayChar and the empty 	spaces so that when they were reloaded they were placed in the right spot. This gave me a lot 	of out of bounds errors because it wasn\'92t interpreting spaces the right way. To fix this 	compilation error, I had to go and change every single space to a \'91-\'91 when I saved a file and the 	back into a space when I put it back on the board.\
\
GameBase Exceptions:\
	-For a time I had to have a catch statement to catch string because I was unable to figure out 	why my file was breaking in the GameBase. It turned out that the error stemmed from 	inconsistencies in file naming conventions so the input wasn\'92t corresponding to the proper 	input. \
\
Unsigned/Signed Errors:\
	-As usual there were some signed/unsigned issues wherever I did for-loops. But these are 	simple fixes and they cleaned the code up significantly\
	}