#include "Instance.h"
#include "CellsModel.h"
#include "Cell.h"



namespace Netlist {
CellsModel :: CellsModel ( QObject* parent )
: QAbstractTableModel(parent)
, cell_(NULL)
{ }
CellsModel ::~ CellsModel  (){ }


void   CellsModel :: setCell ( Cell* cell ) 
{
	emit  layoutAboutToBeChanged ();
	cell_ = cell;
	emit  layoutChanged ();
}


int   CellsModel :: rowCount(const  QModelIndex& parent) const
{ 
	return Cell::getAllCells (). size() ;
}

int   CellsModel :: columnCount(const  QModelIndex& parent) const
{ return  1; }

QVariant   CellsModel ::data( const  QModelIndex& index, int  role ) const
{

	if (role == Qt:: DisplayRole) {
	int  row = index.row();
	switch ( index.column () ) {
	case 0:  return  Cell::getAllCells ()[row]->getName (). c_str ();

	}
	}
	return  QVariant ();
}

QVariant   CellsModel :: headerData( int   section, Qt:: Orientation  orientation, int   role ) const
{
	if (orientation  == Qt:: Vertical) return  QVariant ();
	if (role != Qt:: DisplayRole) return  QVariant ();
	switch ( section ) {
	case 0:  return "Cell";
	}
	return  QVariant ();
}
Cell* CellsModel :: getModel ( int row )
{


	return  Cell::getAllCells ()[ row ];
}


void  CellsModel::updateDatas()
{
	emit  layoutAboutToBeChanged ();

	emit  layoutChanged ();
}









}//end netlist
