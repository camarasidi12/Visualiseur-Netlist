#include<QAction>
#include<QMenu>
#include<QApplication>
#include<QMenuBar>
#include "Cell.h"
#include "CellWidget.h"
#include "SaveCellDialog.h"
#include "OpenCellDialog.h"
#include "CellViewer.h"
#include "InstancesWidget.h"
#include "CellsLib.h"
#include "CellsModel.h"

namespace Netlist{
CellViewer :: CellViewer ( QWidget* parent )
: QMainWindow     (parent)
, cellWidget_     (NULL)
, instancesWidget_(NULL)
,cellsLib_(NULL)
, saveCellDialog_(NULL)
{
	cellWidget_      = new  CellWidget  ();
	instancesWidget_=new InstancesWidget();
	instancesWidget_->setCellViewer(this);
	cellsLib_=new CellsLib();
	cellsLib_->setCellViewer(this);
	
	saveCellDialog_ = new  SaveCellDialog();
	setCentralWidget( cellWidget_  );
	QMenu* fileMenu = menuBar()->addMenu( "&File" );
	
		/**************************/
	QAction* action = new  QAction( "Open Cell", this );
	action ->setStatusTip( "load the Cell" );
	action ->setVisible   ( true );
	fileMenu ->addAction( action  );
	connect( action , SIGNAL(triggered ()), this , SLOT(openCell()) );
	/*************************************/
    action = new  QAction( "Save As", this );
	
	connect( this , SIGNAL(cellLoaded()), cellsLib_->getBaseModel() , SLOT(updateDatas()));
	
	action ->setStatusTip( "Save␣to␣disk␣(rename)␣the␣Cell" );
	action ->setShortcut ( QKeySequence("CTRL+S") );
	action ->setVisible   ( true );
	fileMenu ->addAction( action  );
	connect( action , SIGNAL(triggered ()), this , SLOT(saveCell ()) );


	
	/**************************/
	action = new  QAction( "showInstance", this );
	action ->setStatusTip( "show instance" );
	action ->setVisible   ( true );
	fileMenu ->addAction( action  );
	connect( action , SIGNAL(triggered ()), this , SLOT(showInstancesWidget()));
	/******/
	action = new  QAction( "showCellsLib", this );
	action ->setStatusTip( "showCellsLib" );
	action ->setVisible   ( true );
	fileMenu ->addAction( action  );
	connect( action , SIGNAL(triggered ()), this , SLOT(showCellsLib()));
	
	/************************/
	
	action = new  QAction( "&Quit", this );
	action ->setStatusTip( "Exit␣the␣Netlist␣Viewer" );
	action ->setShortcut ( QKeySequence("CTRL+Q") );
	action ->setVisible   ( true );
	fileMenu ->addAction( action  );
	connect( action , SIGNAL(triggered ()), this , SLOT(close ()) );

}

    CellViewer::~CellViewer(){}
/***************************************************************/
 void   CellViewer :: saveCell  ()
{
	Cell* cell = getCell ();
	if ( cell == NULL ) return;
	QString  cellName = cell ->getName (). c_str ();
	if (saveCellDialog_ ->run(cellName )) {
	cell ->setName( cellName.toStdString () );
	cell ->save    ( cellName.toStdString () );
	}
}
       Cell*   CellViewer::getCell () const
       {
		   return cellWidget_->getCell();
	    }
	    
	    void CellViewer::setCell(Cell* cel)
	    {
			instancesWidget_->setCell(cel);
			cellWidget_->setCell(cel);	
		}
		
		void CellViewer::openCell()
		{  Cell* cell=getCell();
		 if ( cell == NULL ) return;
		  QString  cellName = cell ->getName (). c_str ();
		  bool find=false;
	     if (OpenCellDialog::run(cellName)) 
		   {
			     std::vector<Cell*>cel= Cell::getAllCells ();
			     std::vector<Cell*>::iterator icel=cel.begin();
			     for(;icel<cel.end();++icel)
			     {
					 if((*icel)->getName()==cellName.toStdString ())
					 {
						 find=true;
						  setCell(*icel);
					 }
				 }
				 
		 
		      if(!find)
		       {
			        emit cellLoaded();
			        setCell(Cell::load(cellName.toStdString()));
				}
		
		   }
	    }
	/**********showinstance*********************/
	
	 void  CellViewer::showInstancesWidget()
	 {
	   
		  instancesWidget_->show();
		
	 }
	 
	 /*********show cellslib**************/
	 void  CellViewer::showCellsLib()
	 {
		 
		 
		  cellsLib_->show();
		
	 }
			
			
		
}//end namespace
