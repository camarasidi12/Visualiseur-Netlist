// -*- explicit-buffer-name: "CellWidget.cpp<M1-MOBJ/8-10>" -*-

#include  <QResizeEvent>
#include  <QPainter>
#include  <QPen>
#include  <QBrush>
#include  <QFont>
#include  <QPoint>
#include  <QApplication>
#include  "CellWidget.h"
#include  "Term.h"
#include  "Instance.h"
#include  "Symbol.h"
#include  "shape.h"
#include  "Cell.h"
#include <QLine>
#include  "Line.h"
#include  "Node.h"
#include  "Net.h"


namespace Netlist {

  using namespace std;


  ostream& operator<< ( ostream& o, const QRect& rect )
  {
    o << "<QRect x:" << rect.x()
      <<       " y:" << rect.y()
      <<       " w:" << rect.width()
      <<       " h:" << rect.height() << ">";
    return o;
  }


  ostream& operator<< ( ostream& o, const QPoint& p )
  { o << "<QRect x:" << p.x() << " y:" << p.y() << ">"; return o; }



	 CellWidget :: CellWidget(QWidget* parent)
	: QWidget   (parent)
	, cell_     (NULL)
	, viewport_(Box (0 ,0 ,500 ,500))
	{
		setAttribute     (Qt:: WA_OpaquePaintEvent );
		setAttribute     (Qt:: WA_NoSystemBackground );
		setSizePolicy    (QSizePolicy :: Expanding
		// X direction.
		,QSizePolicy :: Expanding );
		// Y direction.
		setFocusPolicy   (Qt:: StrongFocus );
		setMouseTracking(true);
	}


  CellWidget::~CellWidget ()
  { }


  void  CellWidget::setCell ( Cell* cell )
  {
    cell_ = cell;
    repaint();
  }

QSize   CellWidget :: minimumSizeHint ()  const
	{ return  QSize (500 ,500); }
	
	void   CellWidget :: resizeEvent(QResizeEvent* event) {
	const  QSize& size = event ->size ();
	//  Assume  the  resize  is  always  done by  drawing  the  bottom  right  corner.
	viewport_.setX2( viewport_.getX1() + size.width  () );
	viewport_.setY1( viewport_.getY2() - size.height () );
	cerr  << "CellWidget :: resizeEvent ()␣viewport_:" << viewport_  << endl;
}


 void   CellWidget :: keyPressEvent(QKeyEvent* event) {
	event ->ignore ();
	if (event ->modifiers () & (Qt:: ControlModifier|Qt:: ShiftModifier ))
	return;
		switch( event ->key()) {
		case Qt:: Key_Up:    goUp    ();  break;
		case Qt:: Key_Down: goDown  ();  break;
		case Qt:: Key_Left: goLeft  ();  break;
		case Qt:: Key_Right:goRight ();  break;
		default: return;
	}
	event ->accept ();
}
 

 void   CellWidget :: goRight () {
	viewport_.translate( Point (20,0) );
	repaint ();
	}
	void   CellWidget ::goUp() {
	viewport_.translate( Point (0 ,20) );
	repaint ();
 }

void   CellWidget ::goDown() {
	viewport_.translate( Point (0 ,-20) );
	repaint ();
}
void   CellWidget ::goLeft() {
	viewport_.translate( Point (-20 ,0) );
	repaint ();
}
 


  void   CellWidget :: paintEvent (QPaintEvent* event) {
	QPainter  painter(this);
	painter.setBackground( QBrush( Qt:: black ) );
	painter.eraseRect     ( QRect( QPoint (0,0), size() ) );
	painter.setPen( QPen( Qt::darkGreen ,3) );
	
	painter.setBrush( QBrush( Qt::red ) );

	query(1,painter);
	query(2,painter);
	query(3,painter);
	query(4,painter);
	painter.setPen( QPen( Qt::red ,3) );
	query(5,painter);
	
	   
}


void   CellWidget ::query(unsigned  int flags , QPainter& painter) {
		if ((not  cell_) or (not  flags ))  return;
		const  vector <Instance*>& instances = cell_->getInstances ();
		const  vector<Net*> net   = cell_->getNets ();
	for (size_t i=0; i<instances.size() ; ++i) 
	{
		Point           instPos = instances[i]->getPosition ();
		Symbol*           modsymb = instances[i]->getOwner()->getSymbol();
		const  Symbol* symbol   = instances[i]->getMasterCell()->getSymbol ();
		
	   if (not  symbol) continue;
	   
	     const  vector <Shape*>& shapes =symbol ->getShapes ();
			    vector <Shape*>::const_iterator it=shapes.begin();
		
		if (flags==1) 
		{
			  
			     
			   for (; it< shapes.end() ; ++it) 
			  {                   
				    BoxShape* boxShape = dynamic_cast <BoxShape*>(*it);
				     if (boxShape) 
				    { 
					      Box    box   = boxShape ->getBoundingBox ();
					     QRect  rect = boxToScreenRect(box.translate(instPos ));
					   //   painter.drawRect(rect);
				    }
		      }
       
       }
       
		if(flags==2)
		   {
			   
			  
			   for (; it< shapes.end() ; ++it) 
			   {                   
				    LineShape* lineShape = dynamic_cast <LineShape*>(*it);
				  
				     if (lineShape) 
				    { 
					      Box    box   = lineShape ->getBoundingBox ();
					      Point p1(box.getX1(),box.getY1());
					      
					      Point p2(box.getX2(),box.getY2());
					      
					      
					      QPoint qp1=pointToScreenPoint(p1.translate(instPos));
					      QPoint qp2=pointToScreenPoint(p2.translate(instPos));
					      QLine  rect = QLine(qp1,qp2);
					      painter.drawLine(rect);
				    }
		       }
			   
			   
		    }
		   
		   
		   if(flags==3)
		   {
			   
			  
			   for (; it< shapes.end() ; ++it) 
			   {                   
				    EllipseShape* elipseShape = dynamic_cast <EllipseShape*>(*it);
				  
				     if (elipseShape) 
				    { 
					      Box    box   = elipseShape ->getBoundingBox ();
					      QRect  rect = boxToScreenRect(box.translate(instPos ));
					      painter.drawEllipse(rect);
				    }
		       }
			   
			   
		    }
		    
		   if(flags==4)
		   {
			   
			  
			   for (; it< shapes.end() ; ++it) 
			   {                   
				    ArcShape* arcShape = dynamic_cast <ArcShape*>(*it);
				  
				     if (arcShape) 
				    { 
					      Box    box   = arcShape ->getBoundingBox ();
					      QRect  rect = boxToScreenRect(box.translate(instPos ));
					      
					      painter.drawArc(rect,arcShape->getStart()*16,arcShape->getSpan()*16);
				    }
		       }
			   
			   
		    }
		    
		   if(flags==5)
		   {
			   
			  //dessin conecter instances
			   for (; it< shapes.end() ; ++it) 
			   {                   
				    TermShape* termShape = dynamic_cast <TermShape*>(*it);
				  
				     if (termShape) 
				    { 
						 Point p=modsymb->getTermPosition(termShape->getTerm());
					      Box    box = termShape ->getBoundingBox ();
					      Term*  term= termShape->getTerm();
					      NodeTerm* nd=term->getNode();
					      QPoint qp1=pointToScreenPoint(term->getPosition());
					      painter.drawPoint(qp1);
					      QRect  rect = boxToScreenRect(box.translate(instPos ));
					     // painter.drawRect(rect);

					    painter.drawText(qp1,QString::fromStdString(termShape->getTerm()->getName()));
				    }
		       }
		       
		       //dessin connecter model
		       const vector<Shape*> modsp=modsymb->getShapes();
			   vector<Shape*>::const_iterator itm=modsp.begin();
			    for (; itm< modsp.end() ; ++itm) 
			   {                   
				    TermShape* termShape = dynamic_cast <TermShape*>(*itm);
				  
				     if (termShape) 
				    { 
						 Point p=modsymb->getTermPosition(termShape->getTerm());
					      Box    box = termShape ->getBoundingBox ();
					      Term*  term= termShape->getTerm();
					      NodeTerm* nd=term->getNode();
					      QPoint qp1=pointToScreenPoint(term->getPosition());
					      painter.drawPoint(qp1);
					      QRect  rect = boxToScreenRect(box);
					     // painter.drawRect(rect);

					    painter.drawText(qp1,QString::fromStdString(termShape->getTerm()->getName()));
				    }
		       }
		    }
		   
		  
		
}
    //dessin des nets
         for(int i=0;i<net.size();i++)
		  {
			  painter.setPen( QPen( Qt::cyan,1));
			 std::vector<Node*> node=net[i]->getNodes();
			 std::vector<Line*>  lines=net[i]->getLines();
			
			 for(int k=0;k<lines.size();k++)
			  {
					   QPoint qp1=pointToScreenPoint(lines[k]->getSourcePosition());
					   QPoint qp2=pointToScreenPoint(lines[k]->getTargetPosition());
					   painter.drawLine(qp1,qp2);
					  
			  }
					painter.setPen( QPen( Qt::darkGreen ,3) );
	     } 
}










}  // Netlist namespace.
