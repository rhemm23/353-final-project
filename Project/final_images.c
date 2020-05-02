
#include "final_images.h"

// 
//  Image data for asteroid
// 

const uint8_t asteroidBitmaps[] =
{
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x07, 0xC0, 0x00, //              #####          
	0x00, 0x3C, 0x7C, 0x00, //           ####   #####      
	0x01, 0xF0, 0x06, 0x00, //        #####         ##     
	0x01, 0x10, 0x06, 0x00, //        #   #         ##     
	0x03, 0x30, 0x02, 0x00, //       ##  ##          #     
	0x02, 0x30, 0x02, 0x00, //       #   ##          #     
	0x06, 0x20, 0x02, 0x00, //      ##   #           #     
	0x04, 0x20, 0x06, 0x00, //      #    #          ##     
	0x1C, 0x20, 0x04, 0x00, //    ###    #          #      
	0x10, 0x60, 0x06, 0x00, //    #     ##          ##     
	0x10, 0xC0, 0x03, 0x80, //    #    ##            ###   
	0x3F, 0x80, 0x01, 0xC0, //   #######              ###  
	0x60, 0x00, 0x00, 0xE0, //  ##                     ### 
	0x60, 0x00, 0x00, 0x60, //  ##                      ## 
	0x40, 0x03, 0x80, 0x20, //  #            ###         # 
	0x40, 0x06, 0xFE, 0x20, //  #           ## #######   # 
	0x40, 0x06, 0x02, 0x20, //  #           ##       #   # 
	0x60, 0x06, 0x03, 0x20, //  ##          ##       ##  # 
	0x30, 0x0C, 0x01, 0xE0, //   ##        ##         #### 
	0x10, 0x38, 0x00, 0xC0, //    #      ###           ##  
	0x18, 0x60, 0x03, 0xC0, //    ##    ##           ####  
	0x08, 0xC0, 0x0F, 0x00, //     #   ##          ####    
	0x0F, 0xC0, 0x18, 0x00, //     ######         ##       
	0x03, 0x00, 0x30, 0x00, //       ##          ##        
	0x01, 0x80, 0x60, 0x00, //        ##        ##         
	0x00, 0x80, 0xE0, 0x00, //         #       ###         
	0x00, 0xE3, 0x80, 0x00, //         ###   ###           
	0x00, 0x3E, 0x00, 0x00, //           #####             
	0x00, 0x00, 0x00, 0x00, //                             
};

// Bitmap sizes for asteroid
const uint8_t asteroidWidthPages = 4;
const uint8_t asteroidWidthPixels = 32;
const uint8_t asteroidHeightPixels = 30;


// The entire alphabet

// 
//  Font data for Microsoft Sans Serif 8pt
// 

// Character bitmaps for Microsoft Sans Serif 8pt
const uint8_t letters[] = 
{
	// @0 'A' (7 pixels wide)
	0x10, //    #   
	0x10, //    #   
	0x28, //   # #  
	0x28, //   # #  
	0x44, //  #   # 
	0x44, //  #   # 
	0x7C, //  ##### 
	0x82, // #     #
	0x82, // #     #
	0x00, //        
	0x00, //        

	// @11 'B' (5 pixels wide)
	0xF0, // #### 
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0xF0, // #### 
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0xF0, // #### 
	0x00, //      
	0x00, //      

	// @22 'C' (6 pixels wide)
	0x78, //  #### 
	0x84, // #    #
	0x80, // #     
	0x80, // #     
	0x80, // #     
	0x80, // #     
	0x80, // #     
	0x84, // #    #
	0x78, //  #### 
	0x00, //       
	0x00, //       

	// @33 'D' (6 pixels wide)
	0xF0, // ####  
	0x88, // #   # 
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x88, // #   # 
	0xF0, // ####  
	0x00, //       
	0x00, //       

	// @44 'E' (5 pixels wide)
	0xF8, // #####
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0xF0, // #### 
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0xF8, // #####
	0x00, //      
	0x00, //      

	// @55 'F' (5 pixels wide)
	0xF8, // #####
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0xF0, // #### 
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0x00, //      
	0x00, //      

	// @66 'G' (6 pixels wide)
	0x78, //  #### 
	0x84, // #    #
	0x80, // #     
	0x80, // #     
	0x9C, // #  ###
	0x84, // #    #
	0x84, // #    #
	0x8C, // #   ##
	0x74, //  ### #
	0x00, //       
	0x00, //       

	// @77 'H' (6 pixels wide)
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0xFC, // ######
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x00, //       
	0x00, //       

	// @88 'I' (1 pixels wide)
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //  
	0x00, //  

	// @99 'J' (4 pixels wide)
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x90, // #  #
	0x90, // #  #
	0x60, //  ## 
	0x00, //     
	0x00, //     

	// @110 'K' (6 pixels wide)
	0x88, // #   # 
	0x90, // #  #  
	0xA0, // # #   
	0xC0, // ##    
	0xC0, // ##    
	0xA0, // # #   
	0x90, // #  #  
	0x88, // #   # 
	0x84, // #    #
	0x00, //       
	0x00, //       

	// @121 'L' (5 pixels wide)
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0xF8, // #####
	0x00, //      
	0x00, //      

	// @132 'M' (7 pixels wide)
	0x82, // #     #
	0x82, // #     #
	0xC6, // ##   ##
	0xC6, // ##   ##
	0xAA, // # # # #
	0xAA, // # # # #
	0x92, // #  #  #
	0x92, // #  #  #
	0x82, // #     #
	0x00, //        
	0x00, //        

	// @143 'N' (6 pixels wide)
	0x84, // #    #
	0xC4, // ##   #
	0xC4, // ##   #
	0xA4, // # #  #
	0xA4, // # #  #
	0x94, // #  # #
	0x8C, // #   ##
	0x8C, // #   ##
	0x84, // #    #
	0x00, //       
	0x00, //       

	// @154 'O' (6 pixels wide)
	0x78, //  #### 
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x78, //  #### 
	0x00, //       
	0x00, //       

	// @165 'P' (6 pixels wide)
	0xF8, // ##### 
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0xF8, // ##### 
	0x80, // #     
	0x80, // #     
	0x80, // #     
	0x80, // #     
	0x00, //       
	0x00, //       

	// @176 'Q' (6 pixels wide)
	0x78, //  #### 
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x94, // #  # #
	0x8C, // #   ##
	0x78, //  #### 
	0x04, //      #
	0x00, //       

	// @187 'R' (6 pixels wide)
	0xF8, // ##### 
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0xF8, // ##### 
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x00, //       
	0x00, //       

	// @198 'S' (5 pixels wide)
	0x70, //  ### 
	0x88, // #   #
	0x80, // #    
	0x80, // #    
	0x70, //  ### 
	0x08, //     #
	0x08, //     #
	0x88, // #   #
	0x70, //  ### 
	0x00, //      
	0x00, //      

	// @209 'T' (5 pixels wide)
	0xF8, // #####
	0x20, //   #  
	0x20, //   #  
	0x20, //   #  
	0x20, //   #  
	0x20, //   #  
	0x20, //   #  
	0x20, //   #  
	0x20, //   #  
	0x00, //      
	0x00, //      

	// @220 'U' (6 pixels wide)
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x78, //  #### 
	0x00, //       
	0x00, //       

	// @231 'V' (7 pixels wide)
	0x82, // #     #
	0x82, // #     #
	0x44, //  #   # 
	0x44, //  #   # 
	0x44, //  #   # 
	0x28, //   # #  
	0x28, //   # #  
	0x10, //    #   
	0x10, //    #   
	0x00, //        
	0x00, //        

	// @242 'W' (11 pixels wide)
	0x80, 0x20, // #         #
	0x80, 0x20, // #         #
	0x44, 0x40, //  #   #   # 
	0x44, 0x40, //  #   #   # 
	0x44, 0x40, //  #   #   # 
	0x2A, 0x80, //   # # # #  
	0x2A, 0x80, //   # # # #  
	0x11, 0x00, //    #   #   
	0x11, 0x00, //    #   #   
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @264 'X' (7 pixels wide)
	0x82, // #     #
	0x82, // #     #
	0x44, //  #   # 
	0x28, //   # #  
	0x10, //    #   
	0x28, //   # #  
	0x44, //  #   # 
	0x82, // #     #
	0x82, // #     #
	0x00, //        
	0x00, //        

	// @275 'Y' (7 pixels wide)
	0x82, // #     #
	0x82, // #     #
	0x44, //  #   # 
	0x28, //   # #  
	0x10, //    #   
	0x10, //    #   
	0x10, //    #   
	0x10, //    #   
	0x10, //    #   
	0x00, //        
	0x00, //        

	// @286 'Z' (7 pixels wide)
	0xFE, // #######
	0x02, //       #
	0x04, //      # 
	0x08, //     #  
	0x10, //    #   
	0x20, //   #    
	0x40, //  #     
	0x80, // #      
	0xFE, // #######
	0x00, //        
	0x00, //        

	// @297 'a' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x70, //  ### 
	0x08, //     #
	0x78, //  ####
	0x88, // #   #
	0x88, // #   #
	0x78, //  ####
	0x00, //      
	0x00, //      

	// @308 'b' (5 pixels wide)
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0xF0, // #### 
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0xF0, // #### 
	0x00, //      
	0x00, //      

	// @319 'c' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x70, //  ### 
	0x88, // #   #
	0x80, // #    
	0x80, // #    
	0x88, // #   #
	0x70, //  ### 
	0x00, //      
	0x00, //      

	// @330 'd' (5 pixels wide)
	0x08, //     #
	0x08, //     #
	0x08, //     #
	0x78, //  ####
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x78, //  ####
	0x00, //      
	0x00, //      

	// @341 'e' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x70, //  ### 
	0x88, // #   #
	0xF8, // #####
	0x80, // #    
	0x88, // #   #
	0x70, //  ### 
	0x00, //      
	0x00, //      

	// @352 'f' (2 pixels wide)
	0x40, //  #
	0x80, // # 
	0x80, // # 
	0xC0, // ##
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x00, //   
	0x00, //   

	// @363 'g' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x78, //  ####
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x78, //  ####
	0x08, //     #
	0xF0, // #### 

	// @374 'h' (5 pixels wide)
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0xB0, // # ## 
	0xC8, // ##  #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x00, //      
	0x00, //      

	// @385 'i' (1 pixels wide)
	0x80, // #
	0x00, //  
	0x00, //  
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //  
	0x00, //  

	// @396 'j' (1 pixels wide)
	0x80, // #
	0x00, //  
	0x00, //  
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #

	// @407 'k' (5 pixels wide)
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0x90, // #  # 
	0xA0, // # #  
	0xC0, // ##   
	0xA0, // # #  
	0x90, // #  # 
	0x88, // #   #
	0x00, //      
	0x00, //      

	// @418 'l' (1 pixels wide)
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //  
	0x00, //  

	// @429 'm' (7 pixels wide)
	0x00, //        
	0x00, //        
	0x00, //        
	0xEC, // ### ## 
	0x92, // #  #  #
	0x92, // #  #  #
	0x92, // #  #  #
	0x92, // #  #  #
	0x92, // #  #  #
	0x00, //        
	0x00, //        

	// @440 'n' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0xB0, // # ## 
	0xC8, // ##  #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x00, //      
	0x00, //      

	// @451 'o' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x70, //  ### 
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x70, //  ### 
	0x00, //      
	0x00, //      

	// @462 'p' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0xF0, // #### 
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0xF0, // #### 
	0x80, // #    
	0x80, // #    

	// @473 'q' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x78, //  ####
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x78, //  ####
	0x08, //     #
	0x08, //     #

	// @484 'r' (2 pixels wide)
	0x00, //   
	0x00, //   
	0x00, //   
	0xC0, // ##
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x00, //   
	0x00, //   

	// @495 's' (4 pixels wide)
	0x00, //     
	0x00, //     
	0x00, //     
	0x60, //  ## 
	0x90, // #  #
	0x40, //  #  
	0x20, //   # 
	0x90, // #  #
	0x60, //  ## 
	0x00, //     
	0x00, //     

	// @506 't' (2 pixels wide)
	0x00, //   
	0x80, // # 
	0x80, // # 
	0xC0, // ##
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x40, //  #
	0x00, //   
	0x00, //   

	// @517 'u' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x98, // #  ##
	0x68, //  ## #
	0x00, //      
	0x00, //      

	// @528 'v' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x88, // #   #
	0x88, // #   #
	0x50, //  # # 
	0x50, //  # # 
	0x20, //   #  
	0x20, //   #  
	0x00, //      
	0x00, //      

	// @539 'w' (7 pixels wide)
	0x00, //        
	0x00, //        
	0x00, //        
	0x92, // #  #  #
	0x92, // #  #  #
	0xAA, // # # # #
	0xAA, // # # # #
	0x44, //  #   # 
	0x44, //  #   # 
	0x00, //        
	0x00, //        

	// @550 'x' (4 pixels wide)
	0x00, //     
	0x00, //     
	0x00, //     
	0x90, // #  #
	0x90, // #  #
	0x60, //  ## 
	0x60, //  ## 
	0x90, // #  #
	0x90, // #  #
	0x00, //     
	0x00, //     

	// @561 'y' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x48, //  #  #
	0x48, //  #  #
	0x48, //  #  #
	0x48, //  #  #
	0x30, //   ## 
	0x20, //   #  
	0x20, //   #  
	0xC0, // ##   

	// @572 'z' (4 pixels wide)
	0x00, //     
	0x00, //     
	0x00, //     
	0xF0, // ####
	0x10, //    #
	0x20, //   # 
	0x40, //  #  
	0x80, // #   
	0xF0, // ####
	0x00, //     
	0x00, //     
};

typedef struct {
  uint16_t width;
  uint16_t offset;
} FONT_CHAR_INFO;

// Character descriptors for Microsoft Sans Serif 8pt
// { [Char width in bits], [Offset into microsoftSansSerif_8ptCharBitmaps in bytes] }
const FONT_CHAR_INFO microsoftSansSerif_8ptDescriptors[] = 
{
	{7, 0}, 		// A 
	{5, 11}, 		// B 
	{6, 22}, 		// C 
	{6, 33}, 		// D 
	{5, 44}, 		// E 
	{5, 55}, 		// F 
	{6, 66}, 		// G 
	{6, 77}, 		// H 
	{1, 88}, 		// I 
	{4, 99}, 		// J 
	{6, 110}, 		// K 
	{5, 121}, 		// L 
	{7, 132}, 		// M 
	{6, 143}, 		// N 
	{6, 154}, 		// O 
	{6, 165}, 		// P 
	{6, 176}, 		// Q 
	{6, 187}, 		// R 
	{5, 198}, 		// S 
	{5, 209}, 		// T 
	{6, 220}, 		// U 
	{7, 231}, 		// V 
	{11, 242}, 		// W 
	{7, 264}, 		// X 
	{7, 275}, 		// Y 
	{7, 286}, 		// Z 
	{0, 0}, 		// [ 
	{0, 0}, 		// Backslash
	{0, 0}, 		// ] 
	{0, 0}, 		// ^ 
	{0, 0}, 		// _ 
	{0, 0}, 		// ` 
	{5, 297}, 		// a 
	{5, 308}, 		// b 
	{5, 319}, 		// c 
	{5, 330}, 		// d 
	{5, 341}, 		// e 
	{2, 352}, 		// f 
	{5, 363}, 		// g 
	{5, 374}, 		// h 
	{1, 385}, 		// i 
	{1, 396}, 		// j 
	{5, 407}, 		// k 
	{1, 418}, 		// l 
	{7, 429}, 		// m 
	{5, 440}, 		// n 
	{5, 451}, 		// o 
	{5, 462}, 		// p 
	{5, 473}, 		// q 
	{2, 484}, 		// r 
	{4, 495}, 		// s 
	{2, 506}, 		// t 
	{5, 517}, 		// u 
	{5, 528}, 		// v 
	{7, 539}, 		// w 
	{4, 550}, 		// x 
	{5, 561}, 		// y 
	{4, 572}, 		// z 
};

typedef struct {
  uint8_t char_height;
  char start_char;
  char end_char;
  uint8_t space_width;
  const FONT_CHAR_INFO *descriptors;
  const uint8_t *letters;
} FONT_INFO;

// Font information for Microsoft Sans Serif 8pt
const FONT_INFO letters_info[] =
{
	2, //  Character height
	'A', //  Start character
	'z', //  End character
	2, //  Width, in pixels, of space character
	microsoftSansSerif_8ptDescriptors, //  Character descriptor array
	letters, //  Character bitmap array
};