#include "XMLSaxParser.hpp"

XmlSaxParser::XmlSaxParser()
{
}

XmlSaxParser::~XmlSaxParser ()
{		
	basicAttributes.clear();
}


bool XmlSaxParser::readAndParseNextXmlLine(istream& stream)
{
	if (readNextXmlLine(stream))
	{
		parseCurrentXmlLine();
		return true;
	}
	else
		return false;
	
}

bool XmlSaxParser::isWhiteSpace(char c)
{
	return (c==' ' || c=='\n' || c=='\t');
}
string XmlSaxParser::readNextFundamentalStringValue(istream& stream)
{
	string line="";
	
	if (!stream.eof())
	{
		while (!stream.eof() && isWhiteSpace(stream.peek()))
			stream.get();
		while (!stream.eof() && stream.peek()!='<')
			line.push_back(stream.get());
	}
	return line;
}

bool XmlSaxParser::readNextXmlLine(istream& stream)
{
	int i;
	string line;
	bool comment=true;
	
	while (comment)
	{
		line.resize(1);
		if (!stream.eof())
		{
			line[0] = stream.get();
			while (!stream.eof() && line[0]!='<')
				line[0] = stream.get();
			i=0;
			while (!stream.eof() && line[i]!='>')
			{			
				i++;
				line.push_back(stream.get());
			}
		
			if (line.size()==1)
				return false;
			else
			{
				currentXmlLine = line;
				comment = isComment();
			}
		}
		else
			return false;
	}

	return true;		
}
	
void XmlSaxParser::parseCurrentXmlLine()
{
	int i;
	string argName;
	int argValueStart,argValueStop,argNameStart,argNameStop;
		
	basicAttributes.clear();
	
	currentLineCopy = currentXmlLine;
	
	if (isOpeningTag())
	{
		i=1;
		while (currentXmlLine[i]!=' ' && currentXmlLine[i]!='\n' && currentXmlLine[i]!='\t' && currentXmlLine[i]!='>')
			i++;
		tagName = currentXmlLine.substr(1,i-1);
	}
	else
	{
		i=2;
		while (currentXmlLine[i]!='>')
			i++;
		tagName = currentXmlLine.substr(2,i-2);
	}	
	
	argNameStop = findCar(0,'=')-1;	
	while (argNameStop>0 && currentXmlLine[argNameStop]==' ' && currentXmlLine[i]!='\n' && currentXmlLine[i]!='\t')
		argNameStop--;
	argNameStart = argNameStop;
	
	while (argNameStop>0) // car findCar retourne -1 si non trouve
	{
		while (currentXmlLine[argNameStart]!=' ' && currentXmlLine[i]!='\n' && currentXmlLine[i]!='\t')
			argNameStart--;
		argNameStart++; // on est sur le premier car de l'argname
		
		argName = currentLineCopy.substr(argNameStart,argNameStop-argNameStart+1);
		argValueStart = findCar(argNameStop,'"')+1;
		argValueStop = findCar(argValueStart,'"')-1;
		
		basicAttributes[argName] = currentLineCopy.substr(argValueStart,argValueStop-argValueStart+1);
		
		argNameStop = findCar(argValueStop,'=') - 1;
		while (argNameStop>0 && currentXmlLine[argNameStop]==' ')
			argNameStop--;
		argNameStart = argNameStop;
	}
	
	//basicAttributes["vv3"]="[{25.21739 117.3333 34.76191} {77.82609 99.33334 45.23809} {23.47826 126 11.42857} {75.21739 82.66666 68.09524}]";
	//map<string,string>::iterator ii = basicAttributes.begin();
	//map<string,string>::iterator iend = basicAttributes.end();
	//for(;ii!=iend;++ii)
	//	cerr << (*ii).first << " | " << (*ii).second << endl;
		
}

int XmlSaxParser::findCar(int i,char c)
{
	int j;
	j=i;
	while (static_cast<unsigned int>(j)<=currentXmlLine.length() && currentXmlLine[j]!=c)
		j++;
	
	if (static_cast<unsigned int>(j)>currentXmlLine.length())
		j=-1;
		
	return j;
}

bool XmlSaxParser::isFullTag()
{	
	return (isOpeningTag() && currentXmlLine[currentXmlLine.length()-2]=='/');
}

bool XmlSaxParser::isOpeningTag()
{
	return (currentXmlLine[1]!='/');
}

bool XmlSaxParser::isClosingTag()
{
	return (!isOpeningTag());
}

bool XmlSaxParser::isComment()
{
	if (currentXmlLine.length()<7)
		return false;
	
	return (currentXmlLine[1]=='!' && currentXmlLine[2]=='-' && currentXmlLine[3]=='-');
}

string XmlSaxParser::getTagName()
{
	return tagName;
}
	           
string XmlSaxParser::getArgumentValue(const string& argName)
{
	map<string,string>::iterator ita = basicAttributes.find(argName);
	
	if (ita == basicAttributes.end())
		return NULL;

	return basicAttributes[argName];

}

const map<string,string>& XmlSaxParser::getBasicAttributes()
{
	return basicAttributes;
}


void XmlSaxParser::deleteBasicAttribute(const string& name)
{
	basicAttributes.erase(name);	
}



