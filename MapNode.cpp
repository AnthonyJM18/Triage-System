/* Program		: MapNode.cpp
*  Author		: Anthony Merante
*  Date			: November 3, 2019
*  Description	: Method definitions for the MapNode class
*/
#include "MapNode.hpp"

// Gets type
int MapNode::getType()
{
	return type;
}
// Gets Contagious
int MapNode::getContagious()
{
	return contagious;
}
// Gets time criticality
int MapNode::getTimeCriticality()
{
	return timeCriticality;
}
// sets type
void MapNode::setType(int t)
{
	type = t;
}
// sets contagious
void MapNode::setContagious(int s)
{
	contagious = s;
}
// sets time criticallity
void MapNode::setTimeCriticality(int tc)
{
	timeCriticality = tc;
}

/* Method name	: operator = overload
*  Accepts		: Mapnode containing the data the node will contain
*  Returns		: void
*  Description	: assigns the mapnode values from the passed in node
*/
void MapNode::operator=(MapNode m)
{
	setType(m.getType());
	setContagious(m.getContagious());
	setTimeCriticality(m.getTimeCriticality());
}
