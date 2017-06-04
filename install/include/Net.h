#ifndef  NETLIST_Net_H   
#define  NETLIST_Net_H  
#include "XmlUtil.h"
#include <string>
#include<Term.h>


  namespace Netlist {
  //class Node;
  class Line;
  class Term;
 
  class Net {
   public:
   
    static Net* fromXml(Cell*, xmlTextReaderPtr);
  public :
  //constructer et destructer
         Net(Cell*, const std::string&, Term::Type);
        ~Net();
     
       void  save () const;
 // accesseur
       Cell*                     getCell       () const;
       const std::string&        getName       () const;
       unsigned int              getId         () const;
       Term::Type                getType       () const;
       const std::vector<Node*>& getNodes      () const;
       size_t                    getFreeNodeId () const;
       
       void toXml ( ostream& stream )const;
       
       //tme7
       inline const std::vector<Line*>& getLines () ;
       inline Node*     getNode(size_t)const;
         void  add ( Line* line );
         bool  remove ( Line* line );
// modificateur 
       void  add    ( Node* );
       bool  remove ( Node* );
  //les attribut
  private:
        Cell*               owner_;
        std::string         name_;
        unsigned int        id_;
        Term::Type          type_;
        std::vector<Node*>  nodes_;
        vector<Line*> lines_;
  };// fin classe




inline const std::vector<Line*>& Net::getLines () 
{ return lines_; }


 inline Node*     Net::getNode( size_t id )const{vector<Node*>::const_iterator i=nodes_.begin();
	 Node*  t;
	 for(;i<nodes_.end();++i){
					if(*i!=NULL){
					 if(id==(*i)->getId()){
						 t=*i;
					 }
				 }
				 }
				 
				return t;
				 }







}// fin namespace

#endif
