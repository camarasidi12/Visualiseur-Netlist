	 
	#ifndef NETLIST_Shape_H
	#define NETLIST_Shape_H
	//#include "Symbol.h"
	
	 namespace Netlist {using namespace std;
		 class Box;
		class Symbol;
		class Cell;
		class Term;
	  class  Shape {
	  public:
	  static Shape* fromXml(Symbol*, xmlTextReaderPtr);
	   virtual void  toXml( std::ostream& ) const=0;
	  Shape            ( Symbol* );
	  virtual          ~Shape            ();
	  inline Cell* getCell();
	  inline   Symbol* getSymbol        ()  const;
	  virtual  Box      getBoundingBox  ()  const = 0;
	  private:
	   Symbol* owner_;
	};
	 
	 
		 
	 class  LineShape:public Shape {
	  public:
	   LineShape ( Symbol* owner , int x1, int y1, int x2, int y2 );
	   ~LineShape        ();
	   Box   getBoundingBox  ()  const;
	   void  toXml( std::ostream& ) const;
	  static LineShape* fromXml(Symbol*, xmlTextReaderPtr);
	  int getX1()const;  int getX2()const;  int getY1()const;  int getY2()const;
	  private:
	   int      x1_ , y1_ , x2_ , y2_;
	} ; 
	   
	   class  BoxShape : public  Shape {
	 public:
	   BoxShape         ( Symbol*, const  Box& );
	   BoxShape         ( Symbol*, int x1 , int y1, int x2, int y2 );
	   static BoxShape* fromXml(Symbol*, xmlTextReaderPtr);
	  ~BoxShape         ();
	   Box   getBoundingBox  ()  const;
	   void  toXml( std::ostream& ) const;
	   private:
	   Box   box_;
	   
	};//fin boxshap
	
	
	
	
	   class  TermShape : public  Shape {
		       public:
		   enum NameAlign { top_left=1, top_right,bottom_left, bottom_right};
		   
	   public:
	  TermShape ( Symbol*, string  name , int x, int y ,NameAlign al);
	  ~TermShape  ();
	   Box          getBoundingBox  ()  const;
	  inline   Term*       getTerm          () const;
	   string aligntoString(NameAlign alg)const;
       static NameAlign stringtoAlign(string alignName) ;
	  static TermShape* fromXml(Symbol*, xmlTextReaderPtr);
	   int getX ()  const;
	   int getY ()  const;
	    NameAlign getAlign ()  const;
	  void  toXml( std::ostream& ) const;
	  private:
	  Term* term_;
	  int    x1_ , y1_;
	  NameAlign align_;
	};// fin term shape
	
	//elipseShape
	
	class  EllipseShape:public Shape{
		public:
	   EllipseShape    ( Symbol*, const  Box& );
	   EllipseShape   ( Symbol*, int x1 , int y1, int x2, int y2 );
	   static EllipseShape* fromXml(Symbol*, xmlTextReaderPtr);
	  ~EllipseShape  ();
	   Box   getBoundingBox  ()  const;
	   void  toXml( std::ostream& ) const;
		
	  private:
	  Box   box_;
		
	};
	
	class ArcShape:public Shape{
		public:
     ArcShape ( Symbol*, const  Box& ,int star,int span);
	 ArcShape ( Symbol*, int x1 , int y1, int x2, int y2,int star,int span);
	 static ArcShape* fromXml(Symbol*, xmlTextReaderPtr);
	  ~ArcShape ();
	   Box   getBoundingBox  ()  const;
	   void  toXml( std::ostream& ) const;
	    int getStart ()  const;
	   int getSpan ()  const;
    private:
	Box   box_;
	int start_,span_;
	};
	
	      inline   Term*       TermShape::getTerm() const{return term_;}
	
	  	 inline  Symbol* Shape:: getSymbol  ()  const { return  owner_; }
	
	   	 inline  Cell* Shape:: getCell  () { return  owner_->getCell(); }
	   	 
	   	 
	   	 
	   	 
	   	 
	   	 
	   	 
	   	 
	   	 
	 }//end Netlist
	#endif
	
