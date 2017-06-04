#include  <QLabel>
#include  <QLineEdit>
#include  <QPushButton>
#include  <QHBoxLayout>
#include  <QVBoxLayout>
#include  <QStandardItemModel>
#include  <QAbstractItemModel>
#include  <QItemSelectionModel>
#include  <QHeaderView>
#include <CellViewer.h>
#include <CellsLib.h>
#include <CellsModel.h>

namespace Netlist {
  
 CellsLib::CellsLib( QWidget* parent):
 QWidget         (parent)
, cellViewer_    (NULL)
, baseModel_     (new  CellsModel(this))
, view_           (new  QTableView(this))
, load_           (new  QPushButton(this))
{
    setAttribute( Qt:: WA_QuitOnClose   , false  );
	setAttribute( Qt:: WA_DeleteOnClose , false );
	setContextMenuPolicy( Qt:: ActionsContextMenu  );
	view_ ->setShowGrid               ( false  );
	view_ ->setAlternatingRowColors( true );
	view_ ->setSelectionBehavior    ( QAbstractItemView :: SelectRows  );
	view_ ->setSelectionMode         ( QAbstractItemView :: SingleSelection  );
	view_ ->setSortingEnabled       ( true );
	view_ ->setModel                  ( baseModel_  );
	QHeaderView* horizontalHeader = view_ ->horizontalHeader ();
	horizontalHeader ->setDefaultAlignment   ( Qt:: AlignHCenter  );
	horizontalHeader ->setMinimumSectionSize( 300 );
	horizontalHeader ->setStretchLastSection( true );
	QHeaderView* verticalHeader = view_ ->verticalHeader ();
	verticalHeader ->setVisible( false  );
	load_ ->setText( "Load" );
	connect( load_ , SIGNAL(clicked ()), this , SLOT(load ()) );
	
	setWindowTitle( tr("tme810") );
	QVBoxLayout* vLayout = new  QVBoxLayout  ();
	vLayout ->setSizeConstraint( QLayout :: SetFixedSize  );
	vLayout ->addWidget( view_ );
	
	QHBoxLayout* hLayout = new  QHBoxLayout  ();
	hLayout->addStretch ();
	hLayout ->addWidget (load_ );
		hLayout->addStretch ();
	vLayout->addLayout(hLayout);
	setLayout( vLayout  );
	
	
}
      
  void   CellsLib::setCellViewer( CellViewer* cl)
  { cellViewer_=cl;}
  
 
int   CellsLib :: getSelectedRow  ()  const
{
	QModelIndexList  selecteds = view_ ->selectionModel ()
	->selection (). indexes ();
	if (selecteds.empty ())  return  -1;
	return  selecteds.first ().row ();
}
 
 
 
 void   CellsLib ::load ()
{    
	int  selectedRow = getSelectedRow ();
	if (selectedRow  < 0)  return;
	cellViewer_ ->setCell( baseModel_ ->getModel(selectedRow) );
	
}

















}//end namespac

