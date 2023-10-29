import matplotlib
matplotlib.use('TkAgg')
import numpy as np
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
import Tkinter
import time
import datetime
import os

from Tkinter import *
gui = Tkinter.Tk()
gui.title("Rodent Training")

import serial
run_acquisition=1

#gui.geometry('{}x{}'.format(1500,900))
gui.geometry('{}x{}'.format(1200,800))

class BehaviorGUI:
    def __init__(self, master):
        frame = Tkinter.Frame(master)
        self.master = master
        self.run_acquisition=run_acquisition
        self.dataf=0; self.ser=0; self.get_data=0;
        self.params=0; self.behavior_data=list();
        self.kern=np.ones(10)
        self.dirname='C:\\Users\\S2c_cengrozden\\Desktop\\data\\'

        self.tP=0; self.nO=0; self.o1c=0; self.o2c=0; self.o3c=0; self.o4c=0;
        self.sC=0; self.w4e=0; self.iti=0; self.sT=0; self.oST=0; self.mWP=0;
        self.MWP=0; self.sWP=0; self.cP=0; self.gP=0; self.mRT=0; self.mLD=0;
        self.rD=0; self.fP=0; self.pnsh=0; self.bPs=0; self.fL=0; self.dP=0;
        self.dL=0; self.dtBlank=0; self.dtVideo=0;

        Label(master, text="trainingPhase").place(relx=0.09,rely=0.037,anchor="e")
        self.training_phase= Entry(master,text='training_phase')
        self.training_phase.place(relx=.095, rely=.039, width=30, height=20, anchor="w")
        self.training_phase.insert(10,'2')

        Label(master, text="numOdors").place(relx=0.19,rely=0.037,anchor="e")
        self.numodors= Entry(master,text='numodors')
        self.numodors.place(relx=.195, rely=.039, width=30, height=20, anchor="w")
        self.numodors.insert(10,'1')

        Label(master, text="odor1cond").place(relx=0.09,rely=0.087,anchor="e")
        self.odor1cond= Entry(master,text='odor1cond')
        self.odor1cond.place(relx=.095, rely=.089, width=30, height=20, anchor="w")
        self.odor1cond.insert(10,'0')

        Label(master, text="odor2cond").place(relx=0.19,rely=0.087,anchor="e")
        self.odor2cond= Entry(master,text='odor2cond')
        self.odor2cond.place(relx=.195, rely=.089, width=30, height=20, anchor="w")
        self.odor2cond.insert(10,'0')

        Label(master, text="odor3cond").place(relx=0.09,rely=0.137,anchor="e")
        self.odor3cond= Entry(master,text='odor3cond')
        self.odor3cond.place(relx=.095, rely=.139, width=30, height=20,anchor="w")
        self.odor3cond.insert(10,'10')

        Label(master, text="odor4cond").place(relx=0.19,rely=0.137,anchor="e")
        self.odor4cond= Entry(master,text='odor4cond')
        self.odor4cond.place(relx=.195, rely=.139, width=30, height=20, anchor="w")
        self.odor4cond.insert(10,'10')

        Label(master, text="soundcond").place(relx=0.09,rely=0.187,anchor="e")
        self.soundcond= Entry(master,text='soundcond')
        self.soundcond.place(relx=.095, rely=.189, width=30, height=20, anchor="w")
        self.soundcond.insert(10,'12')

        Label(master, text="com port").place(relx=0.19,rely=0.187,anchor="e")
        self.com_port= Entry(master,text='com_port')
        self.com_port.place(relx=.195, rely=.189, width=30, height=20, anchor="w")
        self.com_port.insert(10,'7')

        Label(master, text="waitforEntry (s)").place(relx=0.07,rely=0.25,anchor="c")
        self.waitforEntry= Entry(master,text='waitForEntry')
        self.waitforEntry.place(relx=.07, rely=.28, width=40, height=20, anchor="c")
        self.waitforEntry.insert(10,'20000')

        Label(master, text="ITI (ms)").place(relx=0.19,rely=0.25,anchor="c")
        self.ITI= Entry(master,text='iti')
        self.ITI.place(relx=.19, rely=.28, width=40, height=20, anchor="c")
        self.ITI.insert(10,'500')

        Label(master, text="settleTime (ms)").place(relx=0.07,rely=0.32,anchor="c")
        self.settleTime= Entry(master,text='settleTime')
        self.settleTime.place(relx=.07, rely=.35, width=40, height=20, anchor="c")
        self.settleTime.insert(10,'100')

        Label(master, text="odorSettleTime (ms)").place(relx=0.19,rely=0.32,anchor="c")
        self.odorSettleTime= Entry(master,text='odorSettleTime')
        self.odorSettleTime.place(relx=.19, rely=.35, width=40, height=20, anchor="c")
        self.odorSettleTime.insert(10,'700')

        Label(master, text="minWait").place(relx=0.07,rely=0.39,anchor="c")
        self.minWaitPeriod= Entry(master,text='minWait')
        self.minWaitPeriod.place(relx=.07, rely=.42, width=40, height=20, anchor="c")
        self.minWaitPeriod.insert(10,'100')

        Label(master, text="maxWait").place(relx=0.19,rely=0.39,anchor="c")
        self.maxWaitPeriod= Entry(master,text='maxWait')
        self.maxWaitPeriod.place(relx=.19, rely=.42, width=40, height=20, anchor="c")
        self.maxWaitPeriod.insert(10,'1000')

        Label(master, text="stepWait").place(relx=0.07,rely=0.46,anchor="c")
        self.stepWaitPeriod= Entry(master,text='stepWait')
        self.stepWaitPeriod.place(relx=.07, rely=.49, width=40, height=20, anchor="c")
        self.stepWaitPeriod.insert(10,'50')

        Label(master, text="cueDuration (ms)").place(relx=0.19,rely=0.46,anchor="c")
        self.cuePeriod= Entry(master,text='cueDuration')
        self.cuePeriod.place(relx=.19, rely=.49, width=40, height=20, anchor="c")
        self.cuePeriod.insert(10,'200')

        Label(master, text="getOutTime (ms)").place(relx=0.07,rely=0.53, anchor="c")
        self.getoffPeriod= Entry(master,text='getOutTime')
        self.getoffPeriod.place(relx=.07, rely=.56, width=40, height=20, anchor="c")
        self.getoffPeriod.insert(10,'2200')

        Label(master, text="maxRespTime (ms)").place(relx=0.19,rely=0.53,anchor="c")
        self.maxRespTime= Entry(master,text='maxRespTime')
        self.maxRespTime.place(relx=.19, rely=.56, width=40, height=20, anchor="c")
        self.maxRespTime.insert(10,'10000')

        Label(master, text="minLickDuration (ms)").place(relx=0.07,rely=0.6,anchor="c")
        self.minLickDuration= Entry(master,text='minLickDuration')
        self.minLickDuration.place(relx=.07, rely=.63, width=40, height=20, anchor="c")
        self.minLickDuration.insert(10,'1000')

        Label(master, text="rewardDuration (ms)").place(relx=0.19,rely=0.6,anchor="c")
        self.rewardDuration= Entry(master,text='rewardDuration')
        self.rewardDuration.place(relx=.19, rely=.63, width=40, height=20, anchor="c")
        self.rewardDuration.insert(10,'200')

        Label(master, text="feedbackDuration (ms)").place(relx=0.07,rely=0.67,anchor="c")
        self.feedbackPeriod= Entry(master,text='feedbackDuration')
        self.feedbackPeriod.place(relx=.07, rely=.70, width=40, height=20, anchor="c")
        self.feedbackPeriod.insert(10,'200')

        Label(master, text="punishment (ms)").place(relx=0.19,rely=0.67,anchor="c")
        self.punishment= Entry(master,text='punishment')
        self.punishment.place(relx=.19, rely=.70, width=50, height=20, anchor="c")
        self.punishment.insert(10,'2500')

        Label(master, text="beepShort (ms)").place(relx=0.07,rely=0.74,anchor="c")
        self.beepPeriodShort= Entry(master,text='beepShort')
        self.beepPeriodShort.place(relx=.07, rely=.77, width=40, height=20, anchor="c")
        self.beepPeriodShort.insert(10,'30')

        Label(master, text="freqLaser (Hz)").place(relx=0.19,rely=0.74,anchor="c")
        self.freqLaser= Entry(master,text='freqLaser')
        self.freqLaser.place(relx=.19, rely=.77, width=40, height=20, anchor="c")
        self.freqLaser.insert(10,'20')

        Label(master, text="durPulses (ms)").place(relx=0.07,rely=0.81,anchor="c")
        self.durPulses= Entry(master,text='durPulses')
        self.durPulses.place(relx=.07, rely=.84, width=40, height=20, anchor="c")
        self.durPulses.insert(10,'25')

        Label(master, text="durLaser (ms)").place(relx=0.19,rely=0.81,anchor="c")
        self.durLaser= Entry(master,text='durLaser')
        self.durLaser.place(relx=.19, rely=.84, width=40, height=20, anchor="c")
        self.durLaser.insert(10,'1000')

        Label(master, text="dtBlank").place(relx=0.07,rely=0.88, anchor="c")
        self.dtBlank= Entry(master,text='dtBlank')
        self.dtBlank.place(relx=.07, rely=.91, width=40, height=20, anchor="c")
        self.dtBlank.insert(10,'200')

        Label(master, text="dtVideo").place(relx=0.19,rely=0.88, anchor="c")
        self.dtVideo= Entry(master,text='dtVideo')
        self.dtVideo.place(relx=.19, rely=.91, width=40, height=20, anchor="c")
        self.dtVideo.insert(10,'2000')


        self.fig = Figure()
        self.ax = self.fig.add_subplot(211)
        self.ax2 = self.fig.add_subplot(212)
        self.canvas = FigureCanvasTkAgg(self.fig,master=master)
        self.canvas.draw()
        self.canvas.get_tk_widget().place(relx=.6, rely=.4, width=500, height=600, anchor="c")

        self.button_quit = Button(master, text="quit", width=10, command=master.quit)
        self.button_quit.place(relx=.8, rely=.8, anchor="c")

        self.button_start=Button(master,text='start',width=10, command=self.start)
        self.button_start.place(relx=.4, rely=.8, anchor="c")

        self.button_stop=Button(master,text='stop',width=10, command=self.stop)
        self.button_stop.place(relx=.4, rely=.9, anchor="c")

        self.plot1_flag = IntVar(value=1)
        self.plot1 = Checkbutton(master,text="Odor 1 (black)",variable=self.plot1_flag).place(relx=0.55,rely=0.78)

        self.plot2_flag = IntVar(value=1)
        self.plot2 = Checkbutton(master,text="Odor 2 (red)",variable=self.plot2_flag).place(relx=0.55,rely=0.82)

        self.plot3_flag = IntVar(value=1)
        self.plot3 = Checkbutton(master,text="Odor 3 (cyan)",variable=self.plot3_flag).place(relx=0.55,rely=0.86)

        self.plot4_flag = IntVar(value=1)
        self.plot4 = Checkbutton(master,text="Odor 4 (pink)",variable=self.plot4_flag).place(relx=0.55,rely=0.90)

        self.plot5_flag = IntVar(value=0)
        self.plot5 = Checkbutton(master,text="Go trials (blue)",variable=self.plot5_flag).place(relx=0.65,rely=0.78)

        self.plot6_flag = IntVar(value=0)
        self.plot6 = Checkbutton(master,text="No-Go trials (red)",variable=self.plot6_flag).place(relx=0.65,rely=0.82)

        self.plot7_flag = IntVar(value=0)
        self.plot7 = Checkbutton(master,text="All trials (blue)",variable=self.plot7_flag).place(relx=0.65,rely=0.86)

        Label(master, text="filename").place(relx=0.34,rely=0.837)
        self.filename = Entry(master,text='filename')
        now=datetime.datetime.now()
        fname='D_'+ now.strftime("%Y%m%d_%H%M")
        self.filename.place(relx=.45, rely=.85, anchor="c")
        self.filename.insert(10,fname)

        Label(master, text="trial number").place(relx=0.87,rely=0.187)
        self.trial_num= Entry(master,text='num trials')
        self.trial_num.place(relx=.95, rely=.2, width=40, height=20, anchor="c")
        self.trial_num.insert(10,'0')

        Label(master, text="completed trials").place(relx=0.855,rely=0.237)
        self.comp_num= Entry(master,text='completed trials')
        self.comp_num.place(relx=.95, rely=.25, width=40, height=20, anchor="c")
        self.comp_num.insert(10,'0')

        Label(master, text="correct trials").place(relx=0.87,rely=0.287)
        self.num_correct= Entry(master,text='correct trials')
        self.num_correct.place(relx=.95, rely=.3, width=40, height=20, anchor="c")
        self.num_correct.insert(10,'0')

        Label(master, text="incorrect trials").place(relx=0.86,rely=0.337)
        self.num_incorrect= Entry(master,text='incorrect trials')
        self.num_incorrect.place(relx=.95, rely=.35, width=40, height=20, anchor="c")
        self.num_incorrect.insert(10,'0')

        Label(master, text="overall performance").place(relx=0.84,rely=0.387)
        self.overall= Entry(master,text='overall')
        self.overall.place(relx=.95, rely=.40, width=40, height=20, anchor="c")
        self.overall.insert(10,'0')

        Label(master, text="trial_type").place(relx=0.885,rely=0.437)
        self.trial_type= Entry(master,text='trial type')
        self.trial_type.place(relx=.95, rely=.45, width=40, height=20, anchor="c")
        self.trial_type.insert(10,'1')

    def update_data(self):
        if self.get_data==0:
            self.ser.write(self.params)

        a=self.ser.readline()  # strings
        if (len(a)>1) and (a[0]=='A'):
            a=self.ser.readline()
            if len(a)>1:
                lstdata = a.split()  # a list of string
                nTrials=float(lstdata[0])
                self.get_data=nTrials-1

                if nTrials>0:
                        self.dataf.write(a)
                        self.behavior_data.append(map(float,lstdata))   #list of floats

                        trial_types=zip(*self.behavior_data)[1]        #tuple
                        correct_trials=zip(*self.behavior_data)[2]     #tuple
                        incorrect_trials=zip(*self.behavior_data)[3]
                        no_entry_trials=zip(*self.behavior_data)[4]
                        early_resp_trials=zip(*self.behavior_data)[5]

                        nCorrect=sum(correct_trials)
                        nIncorrect=sum(incorrect_trials)
                        nNoEntry=sum(no_entry_trials)
                        nEarlyResp=sum(early_resp_trials)

                        self.trial_num.delete('0',END)
                        self.trial_num.insert(10,int(nCorrect+nIncorrect+nNoEntry))
                        self.comp_num.delete('0',END)
                        self.comp_num.insert(10,int(nCorrect+nIncorrect))
                        self.num_correct.delete('0',END)
                        self.num_correct.insert(10,int(nCorrect))
                        self.num_incorrect.delete('0',END)
                        self.num_incorrect.insert(10,int(nIncorrect))
                        if (nCorrect+nIncorrect>0):
                            self.overall.delete('0',END)
                            self.overall.insert(10,int(100*nCorrect/(nCorrect+nIncorrect)))

                        p1=self.plot1_flag.get()
                        p2=self.plot2_flag.get()
                        p3=self.plot3_flag.get()
                        p4=self.plot4_flag.get()
                        p5=self.plot5_flag.get()
                        p6=self.plot6_flag.get()
                        p7=self.plot7_flag.get()

                        complete_trials=[i+j for i, j in zip(correct_trials, incorrect_trials)]
                        inds=[i for i, z in enumerate(complete_trials) if z == 1]
                        only_complete=[complete_trials[i] for i in inds]
                        correct_trials=[correct_trials[i] for i in inds]
                        incorrect_trials=[incorrect_trials[i] for i in inds]
                        trial_types=[trial_types[i] for i in inds]

                        ax = self.canvas.figure.axes[0].clear()
                        
                        self.ax.clear()
                        self.ax2.clear()

                        if p1:
                            inds=[i for i, z in enumerate(trial_types) if z == 1]
                            if inds:
                                correctOdor=[correct_trials[i] for i in inds]
                                y1=np.cumsum(correctOdor)
                                y2=range(1,len(inds)+1)
                                self.ax.plot(y2,y1/y2,'k')
                                if len(y2)>9:                            
                                    ys=np.convolve(correctOdor,self.kern,'valid')/10
                                    ys2=range(1,len(ys)+1)
                                    self.ax2.plot(ys2,ys,'k')                                     

                        if p2:
                            inds=[i for i, z in enumerate(trial_types) if z == 2]
                            if inds:
                                correctOdor=[correct_trials[i] for i in inds]
                                y1=np.cumsum(correctOdor)
                                y2=range(1,len(inds)+1)
                                self.ax.plot(y2,y1/y2,'r')                          
                                if len(y2)>9:
                                    ys=np.convolve(correctOdor,self.kern,'valid')/10
                                    ys2=range(1,len(ys)+1)
                                    self.ax2.plot(ys2,ys,'r')                          

                        if p3:
                            inds=[i for i, z in enumerate(trial_types) if z == 3]
                            if inds:
                                correctOdor=[correct_trials[i] for i in inds]
                                y1=np.cumsum(correctOdor)
                                y2=range(1,len(inds)+1)
                                self.ax.plot(y2,y1/y2,'c')
                                if len(y2)>9:
                                    ys=np.convolve(correctOdor,self.kern,'valid')/10
                                    ys2=range(1,len(ys)+1)
                                    self.ax2.plot(ys2,ys,'c')                                      
                                    
                        if p4:
                            inds=[i for i, z in enumerate(trial_types) if z == 4]
                            if inds:
                                correctOdor=[correct_trials[i] for i in inds]
                                y1=np.cumsum(correctOdor)
                                y2=range(1,len(inds)+1)
                                self.ax.plot(y2,y1/y2,'m')                           
                                if len(y2)>9:
                                    ys=np.convolve(correctOdor,self.kern,'valid')/10
                                    ys2=range(1,len(ys)+1)
                                    self.ax2.plot(ys2,ys,'m')

                        if p5:
                            inds=[i for i, z in enumerate(trial_types) if (z==1 or z==3)]
                            if inds:
                                correctOdor=[correct_trials[i] for i in inds]
                                y1=np.cumsum(correctOdor)
                                y2=range(1,len(inds)+1)
                                ax = self.canvas.figure.axes[0]
                                ax.plot(y2,y1/y2,'b')

                        if p6:
                            inds=[i for i, z in enumerate(trial_types) if (z==2 or z==4)]
                            if inds:
                                correctOdor=[correct_trials[i] for i in inds]
                                y1=np.cumsum(correctOdor)
                                y2=range(1,len(inds)+1)
                                ax = self.canvas.figure.axes[0]
                                ax.plot(y2,y1/y2,'r')

                        if p7:
                            correctOdor=correct_trials
                            y1=np.cumsum(correctOdor)
                            y2=range(1,len(correct_trials)+1)
                            ax = self.canvas.figure.axes[0]
                            ax.plot(y2,y1/y2,'b')

                        self.canvas.draw()
                        self.trial_type.delete('0',END)
                        next_trial=zip(*self.behavior_data)[53]
                        self.trial_type.insert(10,int(next_trial[-1]))

        if self.run_acquisition==1:
            gui.after(100,self.update_data)
        else:
            self.stop()


    def start (self):
        self.run_acquisition=1
        self.get_data=0;
        self.behavior_data=list()

        com_port='COM'+self.com_port.get()
        self.ser = serial.Serial(com_port, 115200,timeout=0.1, writeTimeout=None)
        a=self.ser.readline()
        while len(a)!=0:
            a=self.ser.readline()

        self.tP=self.training_phase.get()
        self.nO=self.numodors.get()
        self.o1c=self.odor1cond.get()
        self.o2c=self.odor2cond.get()
        self.o3c=self.odor3cond.get()
        self.o4c=self.odor4cond.get()
        self.sC=self.soundcond.get()
        self.w4e=self.waitforEntry.get()
        self.iti=self.ITI.get()
        self.sT=self.settleTime.get()
        self.oST=self.odorSettleTime.get()
        self.mWP=self.minWaitPeriod.get()
        self.MWP=self.maxWaitPeriod.get()
        self.sWP=self.stepWaitPeriod.get()
        self.cP=self.cuePeriod.get()
        self.gP=self.getoffPeriod.get()
        self.mRT=self.maxRespTime.get()
        self.mLD=self.minLickDuration.get()
        self.rD=self.rewardDuration.get()
        self.fP=self.feedbackPeriod.get()
        self.pnsh=self.punishment.get()
        self.bPs=self.beepPeriodShort.get()
        self.fL=self.freqLaser.get()
        self.dP=self.durPulses.get()
        self.dL=self.durLaser.get()
        self.dtBlank=self.dtBlank.get()
        self.dtVideo=self.dtVideo.get()

        self.params='p'+self.tP+'s'+self.nO+'s'+self.o1c+'s'+self.o2c+'s'+self.o3c+'s'+\
        self.o4c+'s'+self.sC+'s'+self.w4e+'s'+self.iti+'s'+self.sT+'s'+self.oST+'s'+\
        self.mWP+'s'+self.MWP+'s'+self.sWP+'s'+self.cP+'s'+self.gP+'s'+self.mRT+'s'+\
        self.mLD+'s'+self.rD+'s'+self.fP+'s'+self.pnsh+'s'+self.bPs+'s'+self.fL+'s'+\
        self.dP+'s'+self.dL+'s'+self.dtBlank+'s'+self.dtVideo+'e'+'\n'

        f=self.dirname+self.filename.get()+'.txt'
        self.dataf=open(f,'a')
        self.dataf.close()
        self.dataf=open(f,'a')
        self.update_data()

    def stop (self):
        self.run_acquisition=0
        self.get_data=0
        print('finished!')
        self.ser.readline()
        self.ser.close()
        self.dataf.close()

Behaviorgui = BehaviorGUI(gui)
gui.mainloop()
gui.destroy()

