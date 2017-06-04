#include  <libxml/xmlreader.h>
#include "XmlUtil.h"
#include<fstream>
#include "Term.h"
#include "Net.h"    
#include "Node.h"
#include "Cell.h"
#include "Instance.h"

  namespace Netlist { 
   

   //constructer 
   Instance::Instance( Cell* owner, Cell* model, const std::string& name ):owner_(owner),masterCell_(model),name_(name),position_(){
  
  owner_->add(this);   masterCell_->add(this);
  
  vector<Term*>dupterm=model->getTerms();
  
  for ( vector<Term*>::iterator iterm=dupterm.begin() ; iterm !=dupterm.end() ; ++iterm ) {
     add(*iterm);
    }
  
}//fin ctor instanc
 Instance::~Instance(){
	 owner_->remove(this); masterCell_->remove(this);
	 
	while ( not terms_.empty() ) delete *terms_.begin();
  
}//fin dtor


 //getnam
   const std::string& Instance::getName() const{return name_;

}//fin getname

   Cell* Instance::getMasterCell () const{ return masterCell_;

}//fin getmaster
   Cell* Instance::getOwner () const{ return owner_;

}//fin getmaster

   Cell* Instance::getCell       () const{ return owner_;

}//fin getcell

   const std::vector<Term*>& Instance::getTerms() const{ return terms_;

}//fin vect getterm

   Term* Instance::getTerm( const std::string& name) const{
   for ( vector<Term*>::const_iterator iterm=terms_.begin() ; iterm != terms_.end() ; ++iterm ) {
      if ((*iterm)->getName() == name)  return *iterm;
    }
    return NULL;
}//fin getterm

   Point Instance::getPosition() const{ return position_;

}//fin getposition

// modificateur 
   bool  Instance::connect( const std::string& name, Net* net ){
   Term* term = getTerm( name );
    if (term == NULL) return false;
 
    term->setNet( net );
    return true;

}//fin connect
   void  Instance::add( Term* term ){
	  Term* ter = getTerm(term->getName());
   if (ter!=NULL) {
      cerr << "[ERROR] ce term exite deja" << term->getName() << ">." << endl;
    }else{ 
    terms_.push_back(term);}

}//fin add
   void  Instance::remove( Term* ){



}//fin remov

   void  Instance::setPosition( const Point& pt){
     position_.setX(pt.getX());
     position_.setY(pt.getY());
     Point ptermsh, pinstanc;
     pinstanc=getPosition();
     vector<Term*>::const_iterator iterm=terms_.begin();
     for(;iterm<terms_.end();++iterm){
      ptermsh=masterCell_->getSymbol()->getTermPosition(*iterm);
      (*iterm)->setPosition(ptermsh.getX()+pinstanc.getX(),ptermsh.getY()+pinstanc.getY());
      
      
      }
}//fin setposition
   void  Instance::setPosition( int x, int y ){
       position_.setX(x); position_.setY(y);
       
        Point ptermsh, pinstanc;
     pinstanc=getPosition();
     vector<Term*>::const_iterator iterm=terms_.begin();
     for(;iterm<terms_.end();++iterm){
     ptermsh=owner_->getSymbol()->getTermPosition(*iterm);
      (*iterm)->setPosition(ptermsh.getX()+pinstanc.getX(),ptermsh.getY()+pinstanc.getY());
      
      
      }
}//fin setposition


void Instance::toXml ( ostream& stream )const
{
stream  <<indent<< "<instance name=\"" << name_<<"\" mastercell= \""<<masterCell_->getName() <<"\" x=\""<<position_.getX()<<"\" y=\""<<position_.getY()<<"\"/>\n";

}


  Instance* Instance::fromXml(Cell* cl, xmlTextReaderPtr reader){
	  
	  const xmlChar* nodeName = xmlTextReaderConstLocalName(reader);
	   
	   const xmlChar* instanceTag = xmlTextReaderConstString( reader, (const xmlChar*)"instance" );
	   
	     
	      if ( (nodeName == instanceTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT) ) {
			 string insName = xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
			 string master =xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)"mastercell" ));
			 Cell* mastercel=Cell::find(master);
			 
			 int x,y;
		
			 xmlGetIntAttribute(reader,"x",x);
			 xmlGetIntAttribute(reader,"y",y);
			 Instance* inst=new Instance(cl,mastercel,insName);
			 inst->setPosition(x,y);
			   return inst;
		   }
	     
	     return NULL;
  }










}// finnamespace
