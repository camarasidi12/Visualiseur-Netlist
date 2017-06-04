#ifndef NETLIST_InstW_H
#define NETLIST_InstW_H

#include<QTableView>
#include<QPushButton>
#include  <QWidget>
#include "InstancesModel.h"
#include "CellViewer.h"
namespace Netlist {
//class CellViewer;
class Cell;

class InstancesWidget : public QWidget {
    Q_OBJECT;
  public:
                  InstancesWidget ( QWidget* parent=NULL );
            void  setCellViewer   ( CellViewer* );
            void  goTo            ( int );
            int   getSelectedRow  () const;
    inline  void  setCell         ( Cell* );
  public slots:
            void  load            ();
  private:
            CellViewer*     cellViewer_;
           InstancesModel* baseModel_;
            QTableView*     view_;
            QPushButton*    load_;
};


 inline  void  InstancesWidget::setCell( Cell* cel)
 {
	 
	// cellViewer_->setCell(cel);
	 baseModel_->setCell(cel);
	 
 }

}//end namespace

#endif 
