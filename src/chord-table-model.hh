// Copyright (C) 2009-2012, Romain Goffe <romain.goffe@gmail.com>
// Copyright (C) 2009-2012, Alexandre Dupas <alexandre.dupas@gmail.com>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
// 02110-1301, USA.
//******************************************************************************
#ifndef __CHORD_TABLE_MODEL_HH__
#define __CHORD_TABLE_MODEL_HH__

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QString>
#include <QVector>

class CChord;

/*!
  \file chord-table-model.hh
  \class CChordTableModel
  \brief CChordTableModel is a table model that contains CChord objects.

  A CChordTableModel presents data on a grid where the number of rows or
  columns is specified with setRowCount() or setColumnCount(). Adding
  a new data element (CChord) to the model does not require
  indicating its position on the grid as this is automatically
  computed.

  The following example defines a model that may have several columns
  but a single row:

  \code
  CChordTableModel *model = new CChordTableModel;
  model->setRowCount(1);
  model->addItem("\gtab{C}{X32010}");
  model->addItem("\gtab{Am}{X02210}");
  model->addItem("\gtab{G}{X02210}");
  model->addItem("\gtab{D}{XX0232}");
  \endcode

  Intuitively, the example above behaves like a QHBoxLayout whereas in
  this second example, the model presents data on 3 columns but any
  number of rows (thus, the D chord is displayed on the second row):

  \code
  CChordTableModel *model = new CChordTableModel;
  model->setRowCount(3);
  model->addItem("\gtab{C}{X32010}");
  model->addItem("\gtab{Am}{X02210}");
  model->addItem("\gtab{G}{X02210}");
  model->addItem("\gtab{D}{XX0232}");
  \endcode
*/
class CChordTableModel : public QAbstractTableModel
{
  Q_OBJECT

  public:
  /*!
    \enum ChordRoles
    Each CChord object the model has a set of data elements associated with it, each with its own role.
    The roles are used by the view to indicate to the model which type of data it needs.
  */
  enum ChordRoles {
    NameRole = Qt::UserRole + 1, /*!< the name of the chord.*/
    StringsRole = Qt::UserRole + 2, /*!< the strings sequence of the chord.*/
    InstrumentRole = Qt::UserRole + 3, /*!< the instrument of the chord.*/
    ImportantRole = Qt::UserRole + 4, /*!< whether the chord is important.*/
    MaxRole = ImportantRole
  };

  /// Constructor.
  CChordTableModel(QObject *parent=0);

  /// Destructor.
  ~CChordTableModel();

  /*!
    Returns the number of columns.
    \sa setColumnCount, rowCount, setRowCount
  */
  virtual int columnCount(const QModelIndex & index = QModelIndex()) const;

  /*!
    Sets the number of columns to \a value.
    Calling this method defines a "fixed" column count mode which means
    that any item that is added afterwards will start a new row if necessary.
    \sa columnCount, rowCount, setRowCount
  */
  virtual void setColumnCount(int value);

  /*!
    Returns the number of rows.
    \sa setRowCount, columnCount, setColumnCount
  */
  virtual int rowCount(const QModelIndex & index = QModelIndex()) const;

    /*!
    Sets the number of rows to \a value.
    Calling this method defines a "fixed" row count mode which means
    that any item that is added afterwards will start a new column if necessary.
    \sa rowCount, columnCount, setColumnCount
  */
  virtual void setRowCount(int value);

  /* drag and drop */
  Qt::DropActions supportedDropActions() const;
  Qt::DropActions supportedDragActions() const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QStringList mimeTypes() const;
  QMimeData * mimeData(const QModelIndexList &indexes) const;
  bool dropMimeData(const QMimeData *data, Qt::DropAction action,
		    int row, int column, const QModelIndex &parent);

  /*!
    Reimplements QAbstractTableModel::data().
    Returns the item (CChord object) at position \a index according to the role \a role.
    \sa setData
   */
  QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;

  /*!
    Reimplements QAbstractTableModel::setData().
    Sets the value \a value of the item (CChord object) at position \a index for the role \a role.
    \sa data
   */
  bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);


  /*!
    Returns the CChord object at position \a index.
    \sa data, setData
   */
  CChord * getDiagram(const QModelIndex & index) const;

public slots:
  void insertItem(const QModelIndex & index, const QString & value);
  void removeItem(const QModelIndex & index);
  void addItem(const QString & value);

private:
  QModelIndex indexFromPosition(int position);
  int positionFromIndex(const QModelIndex & index) const;

private:
  bool m_fixedColumnCount;
  bool m_fixedRowCount;
  int m_columnCount;
  int m_rowCount;
  QVector<CChord*> m_data;
};

#endif //__CHORD_TABLE_MODEL_HH__
