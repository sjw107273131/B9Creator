/*************************************************************************************
//
//  LICENSE INFORMATION
//
//  BCreator(tm)
//  Software for the control of the 3D Printer, "B9Creator"(tm)
//
//  Copyright 2011-2012 B9Creations, LLC
//  B9Creations(tm) and B9Creator(tm) are trademarks of B9Creations, LLC
//
//  This file is part of B9Creator
//
//    B9Creator is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    B9Creator is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with B9Creator .  If not, see <http://www.gnu.org/licenses/>.
//
//  The above copyright notice and this permission notice shall be
//    included in all copies or substantial portions of the Software.
//
//    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
//    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
//    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
*************************************************************************************/

#include "sliceset.h"
#include "slice.h"
#include "math.h"

#include <QtDebug>


SliceSet::SliceSet(B9ModelInstance* pParentInstance)
{
	if(!pParentInstance)
	{
		qDebug() << "SliceSet Constructor - No Parent Clone Specified!";
	}
	pInstance = pParentInstance;
	pSliceData = NULL;
}
SliceSet::~SliceSet()
{
	pInstance = NULL;
	if(pSliceData != NULL)
	{
		delete pSliceData;
		pSliceData = NULL;
	}
}
bool SliceSet::GenerateSlice(double realAltitude)
{
	int segments;
	int loops;

	//destroy the old slice if there is one:
	if(pSliceData != NULL)
	{
        //qDebug() << "old slice data deleted";
		delete pSliceData;
		pSliceData = NULL;
	}

	//make a new one:
    //qDebug() << "SliceSet::GenerateSlice: Creating New Slice At Altitude: " << realAltitude;

	pSliceData = new Slice(realAltitude);


	segments = pSliceData->GenerateSegments(pInstance);//actually generate the segments inside the slice


    pSliceData->SortSegmentsByX();//sort segments in x direction


    pSliceData->ConnectSegmentNeighbors();//connect adjacent segments

	loops = pSliceData->GenerateLoops();//generate loop structures

    //qDebug() << "SliceSet::GenerateSlice: Segments: " << segments;
    //qDebug() << "SliceSet::GenerateSlice: Loops: " << loops;

	return true;
}
