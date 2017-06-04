#ifndef  NETLIST_Instance_H   
#define  NETLIST_Instance_H  
#include "XmlUtil.h"
#include <string>
#include "Indentation.h"
#include "Node.h"

using namespace std;

  namespace Netlist {
 class Cell;
  class Net;
  class Term;
 class Instance {
	 public :
	 static Instance* fromXml(Cell*, xmlTextReaderPtr);

  public :
      void  save () const;
  //constructer et destructer
         Instance      ( Cell* owner, Cell* model, const std::string& );
        ~Instance      ();
 //accesseur
        const std::string&        getName       () const;
        Cell*                     getMasterCell () const;
        Cell*                     getOwner () const;
        Cell*                     getCell       () const;
        const std::vector<Term*>& getTerms      () const;
        Term*                     getTerm       ( const std::string& ) const;
        Point                     getPosition   () const;
        
        void toXml ( ostream& )const;

// modificateur 
       bool  connect       ( const std::string& name, Net* );
       void  add           ( Term* );
       void  remove        ( Term* );
       void  setPosition   ( const Point& );
       void  setPosition   ( int x, int y );
  private:
         Cell*               owner_;
         Cell*               masterCell_;
         std::string         name_;
         std::vector<Term*>  terms_;
          Point               position_;
    
  };// fin classe

}// fin namespace

#endif
