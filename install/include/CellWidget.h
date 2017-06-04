// -*- explicit-buffer-name: "CellWidget.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_CELL_WIDGET_H
#define NETLIST_CELL_WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QPoint>
class QPainter;
#include "Box.h"


namespace Netlist {

  class Cell;
  class NodeTerm;


class CellWidget : public QWidget {
    Q_OBJECT;
  public:

                    CellWidget         ( QWidget* parent=NULL );
    virtual        ~CellWidget         ();
            void    setCell            ( Cell* );
    inline  Cell*   getCell            () const;
    void   query(unsigned  int flags , QPainter& painter) ;
    inline  int     xToScreenX         ( int x ) const;
    inline  int     yToScreenY         ( int y ) const;
    inline  QRect   boxToScreenRect    ( const Box& ) const;
    inline  QPoint  pointToScreenPoint ( const Point& ) const;
    inline  int     screenXToX         ( int x ) const;
    inline  int     screenYToY         ( int y ) const;
    inline  Box     screenRectToBox    ( const QRect& ) const;
    inline  Point   screenPointToPoint ( const QPoint& ) const;
    virtual QSize   minimumSizeHint    () const;
    virtual void    resizeEvent        ( QResizeEvent* );
  protected:
    virtual void    paintEvent         ( QPaintEvent* );
    virtual void    keyPressEvent      ( QKeyEvent* );
  public slots:
            void    goLeft             ();
            void    goRight            ();
            void    goUp               ();
            void    goDown             ();
  private:
    Cell* cell_;
    Box   viewport_;
};

inline  Cell*   CellWidget::getCell            () const
{return cell_;}

   inline  int  CellWidget::xToScreenX ( int x ) const
     {
		 return x-viewport_.getX1();
	 }
	 
   inline  int  CellWidget::yToScreenY ( int y ) const
     {
		 return viewport_.getY2() -y;
	 }


  inline  int CellWidget::screenXToX ( int x ) const
  {
	  
	  return x+viewport_.getX1();
  }

 inline  int CellWidget::screenYToY ( int y ) const
 {
	return  viewport_.getY2()-y;
 }


  inline  QRect    CellWidget::boxToScreenRect( const Box& box) const
   {
	     int larg=xToScreenX(box.getX2())-xToScreenX(box.getX1());
	     int haut=yToScreenY(box.getY2())-yToScreenY(box.getY1());
	   return QRect(xToScreenX(box.getX1()),yToScreenY(box.getY1()),larg,haut);
   }

 inline  Box CellWidget:: screenRectToBox ( const QRect& rec) const
  {    int *x1,*larg,*y1,*haut;
	  rec.getRect(x1,y1,larg,haut);
	   return Box(screenXToX(*x1),screenYToY(*y1),screenXToX(*larg+*x1)
	   ,screenYToY(*y1+*haut));
  }

   inline  QPoint   CellWidget::pointToScreenPoint ( const Point& point) const
   {
	   return QPoint(xToScreenX(point.getX()),yToScreenY(point.getY()));
   }
   
   inline  Point   CellWidget::screenPointToPoint ( const QPoint& point) const
   {
	   return Point(screenXToX(point.x()),screenYToY(point.y()));
   }





}  // Netlist namespace.

#endif  // NETLIST_CELL_WIDGET_H
