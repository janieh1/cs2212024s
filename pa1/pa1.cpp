/**
 * @file pa1.cpp
 * @author your name(s)
 *
 * Contains basic tests for CPSC 221 PA1
 *
 * THIS FILE WILL NOT BE SUBMITTED TO PRAIRIELEARN
 * 
 * IT IS HIGHLY RECOMMENDED TO ADD YOUR OWN TESTS TO THIS FILE!
 * 
 * Think about the mechanical processes in the other functions you have written.
 * Where are the likely places for the logic to go wrong?
 * Write tests that specifically target these potential weak points!
 * START WITH SMALL TEST CASES!
 */

#include "block.h"
#include "twodlinkedlist.h"

#include <iostream>

using namespace std;
using namespace cs221util;

// Declaration of testing functions.
// Recommended to have a testing function for each major function in Block and/or TwoDLinkedList
void TestRender();
void TestFlipHorizontal();
void TestRenderBlock();
void TestCopy();
void TestDimensions();

// Entry point to your program
int main(void) {

	// Add or remove calls to the declared testing functions as necessary
	TestDimensions();
	TestRender();
	TestFlipHorizontal();
	TestRenderBlock();
	TestCopy();

	return 0;
}

void TestCopy() {
	cout << "testing copy()" << endl;
	cout << "creating list" << endl;
	cout << "Reading input image...";
	PNG inputimg;
	inputimg.readFromFile("input-img/cs-256x224.png");
	cout << " list made." << endl;
	cout << "......copying........." << endl;
	TwoDLinkedList cslist(inputimg, 8, 4);
	TwoDLinkedList cslistcopy; 
	cslistcopy.Copy(cslist);
	cout << "copied with no errors" << endl;
	cout << "dimensions of o.g. list:" << endl;
	cout << "dimension X: " << endl;
	cout << to_string(cslist.GetBlockDimensionX()) << endl;
	cout << "dimension Y: " << endl;
	cout << to_string(cslist.GetBlockDimensionY()) << endl;
	cout << "dimensions of copied list:" << endl;
	cout << "dimension X: " << endl;
	cout << to_string(cslistcopy.GetBlockDimensionX()) << endl;
	cout << "dimension Y: " << endl;
	cout << to_string(cslistcopy.GetBlockDimensionY()) << endl;

    cout << "--------RENDERING WITH COPY---------" << endl;

	cout << "Reading input image...";
	PNG inputimg1;
	inputimg1.readFromFile("input-img/cs-256x224.png");
	cout << " done." << endl;

	cout << "Creating TwoDLinkedList...";
	TwoDLinkedList catfacelist(inputimg1, 8, 4);
	cout << " done." << endl;

    TwoDLinkedList catfacelistcopy;
	cout << "Creating TwoDLinkedList...";
	catfacelistcopy.Copy(catfacelist);
	cout << " done." << endl;

	cout << "Rendering image to output PNG at 1x scale...";
	PNG outputimg1 = catfacelist.Render(1);
	cout << " done." << endl;

	cout << "Rendering image to output PNG at 1x scale...";
	PNG outputimg1copy = catfacelistcopy.Render(1);
	cout << " done." << endl;

	cout << "Writing rendered PNG to file...";
	outputimg1.writeToFile("output-img/cat-face-render-og.png");
	cout << " done." << endl;

	cout << "Writing rendered PNG to file...";
	outputimg1copy.writeToFile("output-img/cat-face-render-copy.png");
	cout << " done." << endl;
}

// Implementation of testing functions
void TestRenderBlock() {
	// cout << "Entered TestRenderBlock...:" << endl;

	// cout << "Reading input image...";
	// PNG inputimg;
	// inputimg.readFromFile("input-img/cat-face_1f431.png");
	// cout << " done." << endl;

	// cout << "building block..." << endl;
	// Block b1;
	// b1.Build(50, 100, 10, 10, inputimg);
	// cout << "done building..." << endl;

	// cout << "rendering with scale 1" << endl;
	// PNG* testimg = new PNG(50, 100);
	// b1.Render(1, 0, 0, *testimg);
	// testimg->writeToFile("output-img/renderTest.png");
	// cout << to_string(testimg->width()) << endl;
	// cout << to_string(testimg->height()) << endl;
	// cout << " done." << endl;

	// cout << "rendering with scale 0.5" << endl;
	// PNG* testimg2 = new PNG(25, 50);
	// b1.Render(0, 0, 0, *testimg2);
	// testimg2->writeToFile("output-img/renderTest3.png");
	// cout << to_string(testimg2->width()) << endl;
	// cout << to_string(testimg2->height()) << endl;
	// cout << " done." << endl;

	// cout << "rendering after flipHorizontal..." << endl;
	// b1.FlipHorizontal();
	// cout << "successful flip" << endl;
	// PNG* testimgFlip = new PNG(50, 100);
	// b1.Render(1, 0, 0, *testimgFlip);
    // testimgFlip->writeToFile("output-img/renderTestFlip.png"); 
	// cout << "done" << endl;
}

/**
 *  Builds a list from an input image, calls Blockify, and renders to a PNG
 */
void TestRender() {
	cout << "Entered TestRender..." << endl;

	cout << "Reading input image...";
	PNG inputimg;
	inputimg.readFromFile("input-img/cat-face_1f431.png");
	cout << " done." << endl;

	cout << "Creating TwoDLinkedList...";
	TwoDLinkedList catfacelist(inputimg, 40, 40);
	cout << " done." << endl;

	cout << "Rendering image to output PNG at 1x scale...";
	PNG outputimg1 = catfacelist.Render(1);
	cout << " done." << endl;

	cout << "Writing rendered PNG to file...";
	outputimg1.writeToFile("output-img/cat-face-render1.png");
	cout << " done." << endl;

	cout << "Rendering image to output PNG at 0.5x scale...";
	PNG outputimg0 = catfacelist.Render(0);
	cout << " done." << endl;

	cout << "Writing rendered PNG to file...";
	outputimg0.writeToFile("output-img/cat-face-render0.png");
	cout << " done." << endl;

	cout << "Rendering image to output PNG at 2x scale...";
	PNG outputimg2 = catfacelist.Render(2);
	cout << " done." << endl;

	cout << "Writing rendered PNG to file...";
	outputimg2.writeToFile("output-img/cat-face-render2.png");
	cout << " done." << endl;

	cout << "Rendering image to output PNG at 3x scale...";
	PNG outputimg3 = catfacelist.Render(3);
	cout << " done." << endl;

	cout << "Writing rendered PNG to file...";
	outputimg3.writeToFile("output-img/cat-face-render3.png");
	cout << " done." << endl;

	cout << "Exiting TestRender...\n" << endl;
}

/**
 *  Builds a list from an input image, calls FlipHorizontal, and renders to a PNG
 */
void TestFlipHorizontal() {
	cout << "Entered TestFlipHorizontal..." << endl;

	cout << "Reading input image...";
	PNG inputimg;
	inputimg.readFromFile("input-img/cs-256x224.png");
	cout << " done." << endl;

	cout << "Creating TwoDLinkedList...";
	TwoDLinkedList cslist(inputimg, 8, 4);
	cout << " done." << endl;

	cout << "Calling FlipHorizontal on list...";
	cslist.FlipHorizontal();
	cout << " done." << endl;

	cout << "Rendering flipped image to output PNG at 1x scale...";
	PNG outputimg = cslist.Render(1);
	cout << " done." << endl;

	cout << "Writing flipped PNG to file...";
	outputimg.writeToFile("output-img/cs-fliphorizontal-8x4.png");
	cout << " done." << endl;

	cout << "Exiting TestFlipHorizontal...\n" << endl;
}

void TestDimensions() {
	cout << "testing dimensions now......" << endl;
	cout << "creating list..." << endl;
	cout << "Reading input image...";
	PNG inputimg;
	inputimg.readFromFile("input-img/cs-256x224.png");
	cout << " done." << endl;


	TwoDLinkedList cslist(inputimg, 8, 4);
	cout << "list created....." << endl;
	cout << "dimension X: " << endl;
	cout << to_string(cslist.GetBlockDimensionX()) << endl;
	cout << "dimension Y: " << endl;
	cout << to_string(cslist.GetBlockDimensionY()) << endl;
	cout << "all done test dimensions!!" << endl;
}
