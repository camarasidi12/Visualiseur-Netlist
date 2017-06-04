// -*- explicit-buffer-name: "Main.cpp<M1-MOBJ/7>" -*-

#include <string>
#include <sstream>
#include <iostream>
#include <memory>
using namespace std;

#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
#include  <QApplication>
#include  <QtGui>
#include "CellViewer.h"
#include "InstancesWidget.h"
using namespace Netlist;


int main ( int argc, char* argv[] )
{
 cout << "Chargement des modeles:" << endl;
  cout << "- <vdd> ..." << endl;
  Cell::load( "vdd" );
  
  cout << "- <TransistorP> ..." << endl;
  Cell::load( "TransistorP" );
  
   cout << "- <TransistorN> ..." << endl;
  Cell::load( "TransistorN" );
  
   cout << "- <gnd> ..." << endl;
  Cell::load( "gnd" );
  
 
  cout << "- <and2> ..." << endl;
  Cell* and2=Cell::load( "and2" );

  cout << "- <or2> ..." << endl;
  Cell::load( "or2" );

  cout << "- <xor2> ..." << endl;
  Cell::load( "xor2" );

  cout << "- <halfadder> ..." << endl;
  Cell* halfadder = Cell::load( "halfadder" );

  cout << "\nContenu du <and2>:" << endl;
  and2->toXml( cout );

  cout << "\nContenu du <halfadder>:" << endl;
  halfadder->toXml( cout );
  /*******************************************************/
	QApplication* qa = new  QApplication(argc ,argv);
	CellViewer* viewer = new  CellViewer  ();
	//InstancesWidget* in = new  InstancesWidget();
	viewer ->setCell( halfadder  );
	viewer->show ();
	int  rvalue = qa ->exec ();
	delete  qa;

  return rvalue;
}


