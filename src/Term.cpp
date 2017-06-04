#include  <libxml/xmlreader.h>
#include "XmlUtil.h"
//#include "XmlUtil.cpp"
#include<fstream>
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"

  namespace Netlist {

  
 
  //constructer cell
    Term::Term ( Cell* cel, const std::string& name, Direction dr ):
    owner_(cel),name_(name),direction_(dr), node_(this,Node::noid),type_(External){
     cel->add(this);
}//fin ctor cell

 // constructeur instance
    Term::Term ( Instance* ins, Term* modelTerm):
    owner_(ins),name_(modelTerm->name_),direction_(modelTerm->direction_),node_(this,Node::noid),type_(Internal){
    ins-> add(this);
   
}//fin  ctor instan

// destructeur
     Term::~Term (){
		 
	  net_->remove(&node_);    //deconexion avec net
       getOwnerCell()->remove(this);
       
     //(*Cell)owner_->remove(name_);  //deconexion avec cell ou instance
     
}//fin dtor

//getOwnerCell
   Cell* Term::getOwnerCell () const{
   if(type_==Internal)  return ((Instance*)owner_)->getCell();
   if(type_==External) return (Cell*)owner_;
}//fin getowner
   

// modificateur 
  void  Term::setNet(Net* ne){
   net_=ne;   
   net_->add(&node_);
}//fin  setnet
  void  Term::setNet( const std::string& ne){
   net_=getOwnerCell()-> getNet(ne);
    net_->add(&node_);
}//fin  setnet
  void  Term::setPosition( const Point& pt){
     node_.setPosition ( pt );
}

  void  Term::setPosition( int x, int y ){
   node_.setPosition ( x, y );
}//fin set position

//tostring()
  std::string Term::toString(Term::Type typ ){
	  if(typ==Term::Internal){
		return "Internal";
		  
		  }else return "External";
	  
	  }
	 
  std::string Term::toString(Direction  direc) {
    switch (direc)
{
     case Term::In :return "In" ;
        
    case Term::Out: return "Out";
     case Term::Inout: return "Inout";
    case Term::Tristate: return "Tristate";
    
    case Term::Transcv: return "Transcv";
    
    case Term::Unknown: return "Unknown";
  
  
  }
}

    Term::Direction Term::toDirection(std::string strg){
	

     if(strg=="In" ) return In ;
        
    if(strg=="Out") return Term::Out;
     if(strg=="Inout") return Term::Inout;
    if(strg=="Tristate") return Term::Tristate;
    
    if(strg=="Transcv") return Term::Transcv;
    
    if(strg=="Unknown") return Term::Unknown;
  
}
  
 void Term::toXml( ostream& stream )const
{
stream<<indent<< "<term name=\"" << name_ <<"\" direction= \""<<Term::toString(direction_)<<"\" x=\""<<node_.getPosition().getX()
<<"\" y=\""<<node_.getPosition().getY()<<"\"/>\n";

}





  Term* Term::fromXml(Cell* cl, xmlTextReaderPtr reader ){
	  
	   const xmlChar* nodeName = xmlTextReaderConstLocalName( reader );
	   
	    const xmlChar* termTag = xmlTextReaderConstString( reader, (const xmlChar*)"term" );
	   
	     
	       if ( (nodeName == termTag)) {
			 string termName = xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
			 string direc =xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)"direction" ));
			
			 Direction direction =Term::toDirection(direc);
			 int x,y;
			 xmlGetIntAttribute(reader,"x",x);
			 xmlGetIntAttribute(reader,"y",y);
			 Term* term=new Term(cl,termName,direction);
			 term->setPosition(x,y);
			   return term;
		   }
	     
	     return NULL;
	     
	  
  }




}// fin namespace

