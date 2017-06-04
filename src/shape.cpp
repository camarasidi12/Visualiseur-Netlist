		#include  <libxml/xmlreader.h>
		#include "XmlUtil.h"
		
		  #include "Box.h"
		  #include "Symbol.h"
		  #include "Term.h"
		  #include "shape.h"
		  #include "Cell.h"
		 
		 
		 
		 namespace Netlist {
			 //description de la class shape
		  Shape::Shape( Symbol* sy ):owner_(sy){}
		  Shape::~Shape(){}
		  
 Shape* Shape::fromXml ( Symbol* owner, xmlTextReaderPtr reader )
{
	// Factory-like method.
	  const xmlChar* boxTag
	    = xmlTextReaderConstString( reader, (const xmlChar*)"box" );
	  const xmlChar* ellipseTag
	    = xmlTextReaderConstString( reader, (const xmlChar*)"ellipse" );
	  const xmlChar* arcTag
	    = xmlTextReaderConstString( reader, (const xmlChar*)"arc" );
	  const xmlChar* lineTag
	    = xmlTextReaderConstString( reader, (const xmlChar*)"line" );
	  const xmlChar* termTag
	    = xmlTextReaderConstString( reader, (const xmlChar*)"term" );
	  const xmlChar* nodeName
	      = xmlTextReaderConstLocalName( reader );
	
	  Shape* shape = NULL;
	  if (boxTag == nodeName)
	    shape = BoxShape::fromXml( owner, reader );
	  if (ellipseTag == nodeName)
	    shape = EllipseShape::fromXml( owner, reader );
	  if (arcTag == nodeName)
	    shape = ArcShape::fromXml( owner, reader );
	  if (lineTag == nodeName)
	    shape = LineShape::fromXml( owner, reader );
	  if (termTag == nodeName)
	    shape = TermShape::fromXml( owner, reader );
	
	  if (shape == NULL)
	    cerr << "[ERROR] Unknown or misplaced tag <" << nodeName << "> (line:"
	         << xmlTextReaderGetParserLineNumber(reader) << ")." << endl;
	
	  return shape;
}
		  // fin description shape
		  
		  //ctor et dtor lineshape et ses autres fonction
		  LineShape :: LineShape ( Symbol* owner , int x1, int y1, int x2, int y2 )
		: Shape(owner), x1_(x1), y1_(y1), x2_(x2), y2_(y2)
		{  owner->add(this);}
		
		LineShape::~LineShape(){}
		
		  Box LineShape::getBoundingBox  ()  const{
			  return Box(x1_,y1_,x2_,y2_);}
			  
			  //accesseeur
		 int LineShape::getX1()const{
				   return x1_;
				   }
			  int LineShape::getX2()const{
				  return x2_;
				  } 
			 int LineShape::getY1()const{
				 return y1_;
				 } 
		    int LineShape::getY2()const{
				
				return y2_;}
			//toxml
			
			void  LineShape::toXml( std::ostream& stream ) const{
				
	stream<<indent << "<line x1=\""<<getX1()<<"\" y1=\""<<getY1()<<"\" x2=\""<<getX2()<<"\" y2=\""<<getY2()<<"\"/>"<<endl;
			}  
		  
		  //lineshap froxml
		   LineShape* LineShape::fromXml(Symbol* sb, xmlTextReaderPtr reader){
			    const xmlChar* nodeName = xmlTextReaderConstLocalName( reader );
			   
			    const xmlChar* lineTag = xmlTextReaderConstString( reader, (const xmlChar*)"line" );
			   
			     
			       if ( (nodeName == lineTag)) {
					 string termName = xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
					
					 int x1,y1,x2,y2;
					 xmlGetIntAttribute(reader,"x1",x1);
					 xmlGetIntAttribute(reader,"y1",y1);
					  xmlGetIntAttribute(reader,"x2",x2);
					 xmlGetIntAttribute(reader,"y2",y2);
					 LineShape* lin=new LineShape(sb,x1,y1,x2,y2);
					 
					   return lin;
				   }
			     
			     return NULL;
			     
			   
		   }
		   //fin description lineshape
		   
		   //descrip boxshap
		   
		   BoxShape :: BoxShape ( Symbol* owner , const  Box& box )
		  : Shape(owner), box_(box)
		   {  owner->add(this);}
		   
		    BoxShape::~BoxShape(){};
		   
		    BoxShape :: BoxShape( Symbol* owner, int x1 , int y1, int x2, int y2 )
		  : Shape(owner),box_(x1,y1,x2,y2){  owner->add(this);}
		   
		   Box   BoxShape :: getBoundingBox  () const
		   { return  box_; }
		   // toxml
		   
		   void  BoxShape ::toXml( std::ostream& stream ) const{
				
	  stream <<indent  << "<box x1=\""<<getBoundingBox().getX1()<<"\" y1=\""<<getBoundingBox().getY1()
	  <<"\" x2=\""<<getBoundingBox().getX2()<<"\" y2=\""<<getBoundingBox().getY2()<<"\"/>"<<endl;
			}  
		   
		   //fromxml de boxshape
		   
		    BoxShape* BoxShape::fromXml(Symbol* sb, xmlTextReaderPtr reader){
			    const xmlChar* nodeName = xmlTextReaderConstLocalName( reader );
			   
			    const xmlChar* boxTag = xmlTextReaderConstString( reader, (const xmlChar*)"box" );
			   
			     
			       if ( (nodeName == boxTag)) {
				
					 int x1,y1,x2,y2;
					 xmlGetIntAttribute(reader,"x1",x1);
					 xmlGetIntAttribute(reader,"y1",y1);
					  xmlGetIntAttribute(reader,"x2",x2);
					 xmlGetIntAttribute(reader,"y2",y2);
					BoxShape* box=new BoxShape(sb,x1,y1,x2,y2);
					 
					   return box;
				   }
			     
			     return NULL;}	     
			// fin description boxshap
			
			//termShape
			
			 TermShape::TermShape ( Symbol* owner, string  name , int x, int y ,TermShape::NameAlign alig):Shape(owner),term_(NULL),
			 x1_(x),y1_(y),align_(alig)
			 {
		        Cell* cell = getCell ();
		       term_ = cell ->getTerm( name );
		       owner->add(this);
		        }
		        
		      TermShape::~TermShape(){};
			 
			 Box TermShape::getBoundingBox  ()  const{
			  return Box(x1_,y1_,x1_,y1_);}
			  
			  //accesseur
			  
			   int TermShape::getX ()  const{
				   return x1_;}
	         int TermShape::getY ()  const{
			   return y1_;
		              }
		              
		    TermShape::NameAlign TermShape::getAlign ()  const{
				   return align_;}
		   
		    string TermShape::aligntoString(TermShape::NameAlign alg)const	{
				switch(alg){
				case TermShape::top_right:return "top_right";
				case TermShape::top_left:return "top_left";
				case TermShape::bottom_right:return "bottom_right";
				case TermShape::bottom_left:return "bottom_left";
				default:return "n'arrivepas";
					
					
				}
			}	   
			
			//stringToAlign
			
		    TermShape::NameAlign TermShape::stringtoAlign(string alignName){
				   if(alignName=="top_right"){return TermShape::top_right;}
				    if(alignName=="top_left"){return TermShape::top_left;}
				    if(alignName=="bottom_right"){return TermShape::bottom_right; }
				    if(alignName=="bottom_left"){return TermShape::bottom_left; }	
			}
	                 
			 //toxml
			   void  TermShape ::toXml( std::ostream& stream ) const{
	      stream  <<indent << "<term name=\""<<getTerm()->getName()<<"\" x1=\""<< getX()<<"\" y1=\""<<getY()
	     <<"\" align=\""<<aligntoString(getAlign())<<"\"/>"<<endl;
			}  
			 
			 //fromxml
			   TermShape* TermShape::fromXml(Symbol* sb, xmlTextReaderPtr reader){
			    const xmlChar* nodeName = xmlTextReaderConstLocalName( reader );
			   
			    const xmlChar* termTag = xmlTextReaderConstString( reader, (const xmlChar*)"term" );
			   
			     
			       if ( (nodeName == termTag)) {
					 string termName = xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
					string align =xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)"align" ));
					
					TermShape::NameAlign aligval;
					 aligval=stringtoAlign(align);
					 int x1,y1;
					 xmlGetIntAttribute(reader,"x1",x1);
					 xmlGetIntAttribute(reader,"y1",y1);
					
					TermShape* term=new TermShape(sb,termName,x1,y1,aligval);
					 
					   return term;
				   }
			     
			     return NULL;}
		   
		   //elipseShap
		   
		   EllipseShape ::EllipseShape ( Symbol* owner , const  Box& box )
		  : Shape(owner), box_(box)
		   {owner->add(this);}
		   
		   EllipseShape::~EllipseShape(){};
		   
		  EllipseShape:: EllipseShape( Symbol* owner, int x1 , int y1, int x2, int y2 )
		  : Shape(owner),box_(x1,y1,x2,y2){owner->add(this); }
		   
		   Box  EllipseShape ::getBoundingBox() const
		   { return  box_; }
		   
		   //toxml
		    void  EllipseShape::toXml( std::ostream& stream ) const{
				
	  stream <<indent << "<ellipse x1=\""<<getBoundingBox().getX1()<<"\" y1=\""<<getBoundingBox().getY1()
	  <<"\" x2=\""<<getBoundingBox().getX2()<<"\" y2=\""<<getBoundingBox().getY2()<<"\"/>"<<endl;
			}  
		   
		   //fromxml
		EllipseShape* EllipseShape::fromXml(Symbol* sb, xmlTextReaderPtr reader){
			    const xmlChar* nodeName = xmlTextReaderConstLocalName( reader );
			   
			    const xmlChar* elipsTag = xmlTextReaderConstString( reader, (const xmlChar*)"ellipse" );
			   
			     
			       if ( (nodeName == elipsTag)) {
				
					 int x1,y1,x2,y2;
					 xmlGetIntAttribute(reader,"x1",x1);
					 xmlGetIntAttribute(reader,"y1",y1);
					  xmlGetIntAttribute(reader,"x2",x2);
					 xmlGetIntAttribute(reader,"y2",y2);
					EllipseShape* elip=new EllipseShape(sb,x1,y1,x2,y2);
					 
					   return elip;
				   }
			     
			     return NULL;}   
		   
		   
		   //fin description elipseShap
		   
		   //description arcShp
		   ArcShape::ArcShape( Symbol* owner , const  Box& box,int star,int span )
		  : Shape(owner), box_(box),start_(star),span_(span)
		   { owner->add(this);}
		   
		   ArcShape::~ArcShape(){};
		   
		  ArcShape:: ArcShape( Symbol* owner, int x1 , int y1, int x2, int y2 ,int star,int span)
		  : Shape(owner),box_(x1,y1,x2,y2),start_(star),span_(span)
		  { owner ->add( this );}
		   
		   //accesseur
		   Box  ArcShape ::getBoundingBox() const
		   { return  box_; }
		   
		    int ArcShape::getStart ()  const{return start_;}
	       int ArcShape::getSpan ()  const{return span_;}
		   //toxml
		    void  ArcShape::toXml( std::ostream& stream ) const{
				
	  stream<<indent  << "<arc x1=\""<<getBoundingBox().getX1()<<"\" y1=\""<<getBoundingBox().getY1()
	  <<"\" x2=\""<<getBoundingBox().getX2()<<"\" y2=\""<<getBoundingBox().getY2()<<"\" start=\""<<getStart()<<
	  "\" span=\""<<getSpan()<<"\"/>"<<endl;
			} 
		   
		   //fromxml
		   ArcShape * ArcShape::fromXml(Symbol* sb, xmlTextReaderPtr reader){
			    const xmlChar* nodeName = xmlTextReaderConstLocalName( reader );
			   
			    const xmlChar* arcTag = xmlTextReaderConstString( reader, (const xmlChar*)"arc" );
			   
			     
			       if ( (nodeName == arcTag)) {
				
					 int x1,y1,x2,y2,span,star;
					 xmlGetIntAttribute(reader,"x1",x1);
					 xmlGetIntAttribute(reader,"y1",y1);
					  xmlGetIntAttribute(reader,"x2",x2);
					 xmlGetIntAttribute(reader,"y2",y2);
					 xmlGetIntAttribute(reader,"start",star);
					 xmlGetIntAttribute(reader,"span",span);
					ArcShape* arc=new ArcShape(sb,x1,y1,x2,y2,star,span);
					 
					   return arc;
				   }
			     
			     return NULL;}   
		   
		   
		   
		   
		   
		   
		   
		   
		   
		   
		   
		 }//end Netlist
		
	
