import serial
import modbus_tk
import modbus_tk.defines as cst
from modbus_tk import modbus_rtu
import matplotlib.pyplot as plt


PORT = '/dev/ttyACM0'
MESNUM = 2000
FREQ = 40 #Hz
dT = 25 #ms
def main():
    #Connect to the slave
    try:
        master = modbus_rtu.RtuMaster(
            serial.Serial(port=PORT, baudrate=115200, bytesize=8, parity='N', stopbits=1, xonxoff=0)
        )
        master.set_timeout(5.0)
        master.set_verbose(True)
        last_sp=0
        data=[0]
        mes=[]
        for i in range(0,MESNUM):
            val=master.execute(1, cst.READ_HOLDING_REGISTERS, 0, 3)[0]
            mes.append(val)
            if val <= last_sp:
                data.append(last_sp)
                last_sp=0
            last_sp+=1
        #print mes
        #data=[x*dT for x in data]
        #print data
        spikes = [-70]
        for i in data:
            for j in range(0,i-2):
                spikes.append(-70)
            spikes.append(40)
            spikes.append(-90)
        plt.plot(spikes)
        plt.show()
    except Exception as exc:
        print exc



if __name__ == "__main__":
    main()