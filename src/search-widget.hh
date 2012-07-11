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

#ifndef __SEARCH_WIDGET_HH
#define __SEARCH_WIDGET_HH

#include <QFrame>

class QPlainTextEdit;
class QSettings;
class QLineEdit;
class QPushButton;

/*!
  \file search-widget.hh
  \class CSearchWidget
  \brief CSearchWidget is a widget to perform search over a text editor.

  \image html search-widget.png

*/
class CSearchWidget : public QFrame
{
  Q_OBJECT
  public:
  CSearchWidget(QWidget *parent = 0);
  virtual ~CSearchWidget();

  /*!
    Sets \a editor as the text editor upon which
    find  operations are applied.
  */
  void setTextEditor(QPlainTextEdit *editor);

  /*!
    Saves the settings of the widget.
    \sa readSettings
  */
  void writeSettings();

  /*!
    Reads the settings of the widget.
    \sa writeSettings
  */
  void readSettings();

public slots:
  /*!
    Finds the next occurrence in the editor's contents
  */
  void find();

private:
  QPlainTextEdit *m_editor;

  QLineEdit *m_findLineEdit;
  QPushButton *m_findPrevButton;
  QPushButton *m_findNextButton;
};

#endif // __SEARCH_WIDGET_HH