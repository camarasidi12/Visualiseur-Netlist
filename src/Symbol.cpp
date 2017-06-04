// -*- explicit-buffer-name: "Symbol.h<M1-MOBJ/7>" -*-




#include  <libxml/xmlreader.h>
#include  <string>
#include  <vector>
#include  "Box.h"
#include "Term.h"
#include "Cell.h"
#include "shape.h"
#include "Symbol.h"


namespace Netlist {

/*  class Term;
  class Cell;
  class LineShape;
  class TermShape;*/
  Symbol::Symbol(Cell* cel):owner_(cel){} 
  
  
  Symbol::~Symbol(){}
                                                                  
      Cell* Symbol:: getCell()const{return owner_;}
      //getboudinbox
      Box Symbol::getBoundingBox() const{
				 Box bx=shapes_[0]->getBoundingBox();
				 for(size_t i=1;i<shapes_.size();++i){
					 bx=bx.merge(shapes_[i]->getBoundingBox());
				 }
				 
				 return bx;}// end getboubox
				 
           
				//gettermShape
             TermShape*   Symbol::getTermShape ( Term* term) const {
				 TermShape* t;
				 for(size_t i=1;i<shapes_.size();++i){
					 t=dynamic_cast<TermShape*>(shapes_[i]);
		             if(t!=NULL){
					 if(t->getTerm()->getName()==term->getName())
					 return t ;
				 }
				 }
				 cout<<"this term doesn't exit:"<<term->getName()<<endl;
				 exit(1);
				
				 }
				 
		Point       Symbol:: getTermPosition ( Term* term ) const 
             { 

				  TermShape* t=NULL;
				  vector<Shape*>::const_iterator it=shapes_.begin();
				 for(;it<shapes_.end();++it){
					 t=dynamic_cast<TermShape*>(*it);
		             if(t!=NULL)
		             {
					    if(t->getTerm()->getName()==term->getName())
					    return term->getPosition(); 
				     }
				 }
				 
			
				}
				
				//add
   
             void  Symbol::add ( Shape* shp){
				 bool exist=false;
		  for ( vector<Shape*>::iterator ishap=shapes_.begin() ; ishap!=shapes_.end() ; ++ishap) {
          if ((*ishap) == shp){
            exist=true;}
                }
              if(not exist){
				shapes_.push_back(shp); }
			 }
				 
				 
				  
             void Symbol::remove ( Shape* shp){
				 
		 for ( vector<Shape*>::iterator ishap=shapes_.begin() ; ishap!=shapes_.end() ; ++ishap) {
          if ((*ishap) == shp){
            shapes_.erase(ishap);
          return;}
           cout<<"ce shape n'existe pas pour l'enlever:"<<endl; 
                }
			 }

             //toxml
            void  Symbol::toXml ( std::ostream& stream) const{
			    stream <<indent++<<"<symbol>" <<endl;
			   for ( vector<Shape*>::const_iterator ishap=shapes_.begin() ; ishap!=shapes_.end() ; ++ishap) {
				  
			    (*ishap)->toXml(stream);
			    
			    
			                               }
				stream <<--indent<<"</symbol>" <<endl;
				 
				 
				 }
                                                      
                                        
           //fromxml
         Symbol*  Symbol::fromXml(Cell* cell, xmlTextReaderPtr reader){
			 const xmlChar* nodeName = xmlTextReaderConstLocalName( reader );
	    enum  State {Beginsymb , Endsymb};
            Symbol* symbol=cell->getSymbol();
	  State state = Endsymb;
	    const xmlChar* symbolTag = xmlTextReaderConstString( reader, (const xmlChar*)"symbol" );
	   
	     
	       if ( (nodeName == symbolTag)) {
			   
			   bool finsymbol=false;
			   
			  
	    while( true){
			
	 int status = xmlTextReaderRead(reader);
      if (status != 1) {
        if (status != 0) {
          cerr << "[ERROR] Cell::fromXml(): Unexpected termination of the XML parser." << endl;
        }
        break;
      }
 
	  nodeName = xmlTextReaderConstLocalName(reader);
    if (finsymbol) {
     
      break;
    }
    
    switch ( xmlTextReaderNodeType(reader) ) {
      case XML_READER_TYPE_COMMENT:
      case XML_READER_TYPE_WHITESPACE:
      case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
        continue;
    }
    
    switch ( state ) {
	
	 case Beginsymb:
        if ( (nodeName == symbolTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT) ) {
          state = Endsymb;
          xmlTextReaderRead(reader);
          continue;
        }
        break;
        case Endsymb:
        if ( (nodeName == symbolTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT) ) {
          finsymbol=true;
          continue;
        } else {
          if(Shape::fromXml(symbol,reader)){
           continue;}
        }
        break;
         default:
          break;
		
	}
   
		   }//fin while
		   return symbol;
		   
	   }else{
		   
		   return NULL;
		   
	   }
   
}
  


}  // Netlist namespace.


