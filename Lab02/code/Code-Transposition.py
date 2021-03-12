import sys
from tkinter import *

class MyCanvas(Canvas):
    def __init__(self, master, hLineWidth=1, vLineWidth=1, radius=2, **kwargs):
        Canvas.__init__(self, master, kwargs)
        self.hLineWidth = hLineWidth
        self.vLineWidth = vLineWidth
        self.radius = radius

    def create_segment_h(self, x, y, l):
        self.create_line(x, y, x + l, y, width=self.hLineWidth)
        self.create_oval(x - self.radius, y - self.radius, x + self.radius, y + self.radius, fill='black')
        self.create_oval(x + l - self.radius, y - self.radius, x + l - self.radius, y + self.radius, fill='black')

    def create_segment_v(self, x, y, l):
        self.create_line(x, y, x, y + l, width=self.vLineWidth)
        self.create_oval(x - self.radius, y - self.radius, x + self.radius, y + self.radius, fill='black')
        self.create_oval(x - self.radius, y + l - self.radius, x + self.radius, y + l + self.radius, fill='black')

    def create_line_h(self, x, y, l):
        self.create_line(x, y, x + l, y, width=self.hLineWidth)

    def create_line_v(self, x, y, l):
        self.create_line(x, y, x, y + l, width=self.vLineWidth)

class Sorter:
    def __init__(self, size):
        self.size = size
        if size > 1:
            self.subSorter = Sorter(size - 1)
    
    def hNum(self):
        return 2 * (self.size - 1)
    
    def draw_all_hlines(self, cvs, x, y, hScale, vScale):   
        '''Create all the horizontal lines in the first place.'''
        leftend = x
        length = hScale * (self.hNum())
        for i in range(1, self.size+1):
            cvs.create_line_h(leftend, y, length)
            y += vScale

    def draw(self, cvs, x, y, hScale, vScale):
        '''Draw the comparators.'''
        if(self.size > 1):
            self.subSorter.draw(cvs,x + 2 * hScale,y,hScale,vScale)
        for i in range(1,self.size):
            cvs.create_segment_v(x,y,vScale)
            x += hScale
            y += vScale

if __name__ == '__main__':
    n = int(input('please input the number n: '))
    sortingNetwork = Sorter(n)

    winW, winH = 2400 * 0.3, 1500 * 0.3
    hMargin, vMargin = winW // 20, winH // 20
    hScale, vScale = (winW - 2 * hMargin) // sortingNetwork.hNum(), (winH - 2 * vMargin) // (n - 1)

    root = Tk()
    root.title('Transposition Network with n=%d (Drawn by Python Tkinter)' %n)
    cvs = MyCanvas(root, bg='white', width = winW, height = winH)
    sortingNetwork.draw_all_hlines(cvs, hMargin, vMargin, hScale, vScale)
    sortingNetwork.draw(cvs, hMargin + hScale, vMargin, hScale, vScale)
    cvs.pack()
    root.mainloop()
