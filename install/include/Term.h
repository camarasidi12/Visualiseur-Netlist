#ifndef  NETLIST_Term_H   
#define  NETLIST_Term_H  
#include "XmlUtil.h"
#include "Node.h"
#include <string>
#include "Indentation.h"


  namespace Netlist {
	 using namespace std;
    //class Node;
    class Net;
    class Cell;
    class Point;
    class Instance;

 class Term {
    public:
   enum Type      { Internal=1, External=2 };
   enum Direction { In=1, Out=2, Inout=3, Tristate=4, Transcv=5, Unknown=6 };
     
     static Term* fromXml(Cell*, xmlTextReaderPtr);
     static std::string toString(Direction );
     static std::string toString(Type );
     static Direction toDirection(std::string );
  //constructer et destructer

  public :
         Term( Cell* , const std::string& name, Direction );
         Term( Instance* , Term* modelTerm);
        ~Term();
        void  save () const;
 //predicat et accesseur
   inline bool               isInternal   () const;
   inline bool               isExternal   () const;
   inline const std::string& getName      () const;
   inline  NodeTerm*         getNode() ;
   inline Net*               getNet       () const;
   inline Cell*              getCell      () const;
       Cell*              getOwnerCell () const;
   inline Instance*          getInstance  () const;
   inline Direction          getDirection () const;
   inline Point              getPosition  () const;
   inline Type               getType      () const;

    void toXml ( ostream& stream )const;
    
// modificateur 
  void  setNet       ( Net* );
  void  setNet       ( const std::string& );
  inline void  setDirection ( Direction );
   void  setPosition  ( const Point& );
   void  setPosition  ( int x, int y );
  private:
         void*         owner_;
         std::string   name_;
         Direction     direction_;
         NodeTerm          node_;
         Type          type_;
         Net*          net_;
        
    
  };// fin classe



  inline bool Term::isInternal() const{if(type_==Internal) return true; else return false;}
  inline bool Term::isExternal   () const{if(type_==External) return true; else return false;}

 inline const std::string& Term::getName() const{return name_;}
 
   inline  NodeTerm* Term::getNode()  {return &node_;}
  
   inline Net*  Term::getNet() const {return net_;}
   
   inline Cell* Term::getCell() const{
	    if(type_==External){
	  return (Cell*)owner_;}
	  else{
		  return NULL;
  }
  }
   
  inline Instance* Term::getInstance() const{
	  if(type_==Internal){
	  return (Instance*)owner_;}
	  else{
		  return NULL;
  }}
  
   inline Term::Direction Term::getDirection() const{return direction_;}
   inline Point  Term::getPosition  () const{return node_.getPosition();}
  inline Term::Type Term::getType() const{return type_;}





}// fin namespace





#endif
