#ifndef NETLIST_CELLVIEW
#define NETLIST_CELLVIEW


#include<QMainWindow>

namespace Netlist{
	class Cell;
	class CellWidget;
	class CellsLib;
	class SaveCellDialog;
	class InstancesWidget;
	class  CellViewer : public  QMainWindow {
	
	 Q_OBJECT;
  public:
                      CellViewer          ( QWidget* parent=NULL );
    virtual          ~CellViewer          ();
            Cell*     getCell             () const;
    inline  CellsLib* getCellsLib         ();  // TME9+.
    
    
    signals :
    void cellLoaded();
  public slots:
            void      setCell             ( Cell* );
            void      saveCell            ();
            void      openCell            ();
            void      showCellsLib        ();  // TME9+.
            void      showInstancesWidget ();  // TME9+.
  private:
    CellWidget*      cellWidget_;
    CellsLib*        cellsLib_;         // TME9+.
    InstancesWidget* instancesWidget_;  // TME9+.
    SaveCellDialog*  saveCellDialog_;
};

CellsLib* CellViewer::getCellsLib (){return cellsLib_;}
}//end namespace

#endif
