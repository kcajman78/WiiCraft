/*---------------------------------------------------------------------------*
  Project:  My template library
  File:     mytl.h

  (C)2005 HUDSON SOFT

  $Header: /home/cvsroot/SDK/include/win32/mytl.h,v 1.2 2006/03/09 12:28:40 yasuh-to Exp $

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef	__MYTL_H__
#define	__MYTL_H__

#include <assert.h>
#include <deque>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
// TMyList
//

template <class T>
class TMYList : public deque<T>
{
public:
	typedef BOOL	(* COMPARE)(T pItem1, LPVOID pData);

	// get the number of lists (to control warnings)
	int	GetCount() { return (int)size(); } 

	// get the list item corresponding to the index
	T	GetItem(int nIndex)
	{
		assert((nIndex >= 0) && (nIndex < GetCount()));
		return at(nIndex);
	}

	// add an item to the end of the list
	int	AddTail(T pItem)
	{
		push_back(pItem);
		return GetCount() - 1;
	}

	// get the index for the specified item
	int	IndexOf(T pItem)
	{
		for (int i=0; i<GetCount(); i++)
		{
			if ( at(i) == pItem ) return i;
		}
		return -1;
	}

	// get the index for the item set to the specified data
	int	IndexOf(LPVOID pData, COMPARE fncCompare)
	{
		assert(fncCompare != NULL);
		for (int i=0; i<GetCount(); i++)
		{
			if ( fncCompare(at(i), pData) ) return i;
		}
		return -1;
	}

	// delete the list item corresponding to the index
	void	Remove(int nIndex, BOOL bDelItem=TRUE)
	{
		assert((nIndex >= 0) && (nIndex < GetCount()));
		if ( bDelItem ) delete at(nIndex);
		erase(begin() + nIndex);
	}

	// delete the specified item
	void	Remove(T pItem, BOOL bDelItem=TRUE)
	{
		int nIndex = IndexOf(pItem);
		assert(nIndex != -1);
		if ( bDelItem ) delete at(nIndex);
		erase(begin() + nIndex);
	}

	// clear the list
	void	Clear(BOOL bDelItem=TRUE)
	{
		if ( bDelItem )
		{
			for (int i=0; i<GetCount(); i++) delete at(i);
		}
		clear();
	}
};

#endif	// __MYTL_H__
