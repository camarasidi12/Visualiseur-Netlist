//#include "Indentation.h"
//#include "Node.h"
#include "XmlUtil.h"
#include<fstream>

#include  <libxml/xmlreader.h>
#include "Line.h"
#include "Term.h"
#include "Net.h"
//#include "Instance.h"
#include "Cell.h"


  namespace Netlist {using namespace std;

 //const size_t  Net::noid = numeric_limits<size_t>::max();

  // destructer
         Net::Net( Cell* cl, const std::string& nm, Term::Type type):owner_(cl),name_(nm),type_(type){
         owner_->add(this);
}//fin ctor
        Net::~Net(){ 
	   owner_->remove(this);
	for ( vector<Node*>::iterator inod=nodes_.begin() ; inod != nodes_.end() ; ++inod ) {
       (*inod)->setId(Node::noid);
    }

}//fin dtor

 // accesseur
       Cell* Net::getCell() const{
        return  owner_;
}//fin getcell
       const std::string& Net::getName() const{
        return name_;
}//fin  getname
       unsigned int Net::getId() const{
       return id_;
}//fin getid
      Term::Type Net::getType() const{return type_;

  }//in getype
       const std::vector<Node*>& Net::getNodes () const{
     return nodes_;
}//fin getnod

       size_t     Net::getFreeNodeId () const{
		  for (size_t i=0;i<nodes_.size(); ++i ) {
			
      if (not nodes_[i])  return i;
       
    }
         return nodes_.size();
       
}//fin getfree
// modificateur 
  
       void  Net::add( Node* nd){
		   if(not nd) return ;
		   size_t id=nd->getId();
		   if(id==Node::noid){
			   id=getFreeNodeId();

		   }
		   if(id<nodes_.size()){
			   if(nodes_[id]!=NULL){
				//cerr<<"error "<<nodes_[id]->getId()<<"  "<<id<<endl   ;
			   }
			   nodes_[id]=nd;
			   }else{
				  for(size_t i=nodes_.size();i<id;++i) nodes_.push_back(NULL);
				  nodes_.push_back(nd); 
		   }
		  
   }// fin add

  
       bool  Net::remove( Node* nd ){
    {
    for ( vector<Node*>::iterator inod=nodes_.begin() ; inod != nodes_.end() ; ++inod ) {
      if (*inod == nd) nd->setId(Node::noid); nodes_.erase(inod); return true;
    }
    return false;
  }
}//fin remov
  //les attribut


void Net::toXml( ostream& stream )const
{string typ=Term::toString(getType()); 
    stream <<indent++<<"<net name=\"" << name_ <<"\" type= \""<<typ<<"\">\n" ;
   
for ( vector<Node*>::const_iterator inod=nodes_.begin() ; inod != nodes_.end() ; ++inod ) {
	if(*inod!=NULL){
      (*inod)->toXml(stream);}
    }
 for ( vector<Line*>::const_iterator ilin=lines_.begin() ; ilin != lines_.end() ; ++ilin ) {
	if(*ilin!=NULL){
      (*ilin)->toXml(stream);}
    }
   stream <<--indent<<"</net>\n";
}




 Net* Net::fromXml(Cell* cl, xmlTextReaderPtr reader){
	 enum  State {Beginnet , Endnet};
              
	  State state = Endnet;
	  const xmlChar* nodeName = xmlTextReaderConstLocalName(reader);
	 
	   
	   const xmlChar* netTag = xmlTextReaderConstString( reader, (const xmlChar*)"net" );
	   //const xmlChar* nodTag = xmlTextReaderConstString( reader, (const xmlChar*)"node" );
	   
	     
	      if ( (nodeName == netTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT)) {
			 string netName = xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
			 string typ =xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)"type" ));
			 Term::Type type;
			  if(typ=="External"){type=Term::External;}
			  else{type=Term::Internal;}
			Net* net=new Net(cl,netName,type);
			
			
	bool finnet=false;
	while( true){
				
	 int status = xmlTextReaderRead(reader);
      if (status != 1) {
        if (status != 0) {
          cerr << "[ERROR] Cell::fromXml(): Unexpected termination of the XML parser." << endl;
        }
        break;
      }		
	  nodeName = xmlTextReaderConstLocalName(reader);
    if (finnet) {
     
      break;
    }
    
    switch ( xmlTextReaderNodeType(reader) ) {
      case XML_READER_TYPE_COMMENT:
      case XML_READER_TYPE_WHITESPACE:
      case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
        continue;
    }
    
    switch ( state ) {
	
	 case Beginnet:
        if ( (nodeName == netTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT) ) {
          state = Endnet;
         
          continue;
        }
        break;
        case Endnet:
        if ( (nodeName == netTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT) ) {
          finnet=true;
         // xmlTextReaderRead(reader);
          continue;
        } else {
          if (Node::fromXml(net,reader))  {continue;}
          if ( Line::fromXml(net,reader))  {continue;}
        }
        break;
		
	}
    
    
		//if(not Node::fromXml(net,reader)) 
				
			}
			   return net;
		   }
	     
	     return NULL;
  }
// tme7
     void  Net::add ( Line* line )
{ if (line) lines_.push_back( line ); }

     
     //remov
     bool  Net::remove ( Line* line )
{
  if (line) {
    for ( vector<Line*>::iterator il = lines_.begin()
        ; il != lines_.end() ; ++il ) {
      if (*il == line) {
        lines_.erase( il );
        return true;
      }
    }
  }
  return false;
}
}// fin namespace























