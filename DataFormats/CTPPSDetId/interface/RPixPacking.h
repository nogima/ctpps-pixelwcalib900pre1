#ifndef DATAFORMATS_RPIXPACKING_H
#define DATAFORMATS_RPIXPACKING_H

#include <utility>
#include "FWCore/Utilities/interface/GCC11Compatibility.h"

class RPixPacking{
 public:
  
  typedef unsigned int PackedDigiType;
  typedef unsigned int ChannelType;
  
  static std::pair<int,int> channelToPixel( int ch) {
    int row = ( ch >> thePacking.column_width) & thePacking.row_mask;
    int col = ch & thePacking.column_mask;
    return std::pair<int,int>(row,col);
  }
  
  static int pixelToChannel( int row, int col) {
    return (row << thePacking.column_width) | col;
  }
  
  
// Pack the pixel information to use less memory
// NOTE: ~ = NOT, 0U = unsigned 0

  class Packing {
  public:
    
 
    Packing(unsigned int row_w, unsigned int column_w,
	    unsigned int time_w, unsigned int adc_w) :
      row_width(row_w), column_width(column_w), adc_width(adc_w)
      ,row_shift(0)
      ,column_shift(row_shift + row_w)
      ,time_shift(column_shift + column_w)
      ,adc_shift(time_shift + time_w)
      ,row_mask(~(~0U << row_w))
      ,column_mask( ~(~0U << column_w))
      ,time_mask(~(~0U << time_w))
      ,adc_mask(~(~0U << adc_w))
      ,rowcol_mask(~(~0U << (column_w+row_w)))
      ,max_row(row_mask)
      ,max_column(column_mask)
      ,max_adc(adc_mask){}

							   
    int row_width;
    int column_width;
    int adc_width;
    
    int row_shift;
    int column_shift;
    int time_shift;
    int adc_shift;
   
    PackedDigiType row_mask;
    PackedDigiType column_mask;
    PackedDigiType time_mask;
    PackedDigiType adc_mask;
    PackedDigiType rowcol_mask;
    
    
    int max_row;
    int max_column;
    int max_adc;
  };
  
 public:
 
  static Packing packing() { return Packing(8, 9, 4, 11);}

  static const Packing thePacking;

 
};  


#endif
