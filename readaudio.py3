import alsaaudio as audio
import time
import audioop


#Input & Output Settings
periodsize = 1024
audioformat = audio.PCM_FORMAT_FLOAT_LE
channels = 16
framerate=8000

#Input Device
inp = audio.PCM(audio.PCM_CAPTURE,audio.PCM_NONBLOCK,device='hw:1,0')
inp.setchannels(channels)
inp.setrate(framerate)
inp.setformat(audioformat)
inp.setperiodsize(periodsize)


#Reading the Input
allData = bytearray()
count = 0
while True:
    #reading the input into one long bytearray
    l,data = inp.read()
    for b in data:
        allData.append(b)

    #Just an ending condition
    count += 1
    if count == 4000:
        break

    time.sleep(.001)


#splitting the bytearray into period sized chunks
list1 = [allData[i:i+periodsize] for i in range(0, len(allData), periodsize)]

#Writing the output
#for arr in list1:
    # I tested writing the arr's to a wave file at this point
    # and the wave file was fine
    #out.write(arr)
