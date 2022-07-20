FROM python:3.8-buster
WORKDIR /app
COPY . .

#RUN apt-get update && apt-get install -y python3-opencv
RUN apt-get update && apt-get install -y libgl1-mesa-dev && install libsm6 libxext6  -y
#RUN add-apt-repository ppa:deadsnakes/ppa -y && apt update
#RUN apt install -y python3.8 libpython3.8 libpython3.8-stdlib python3-pip 
#RUN curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
#RUN python3.8 get-pip.py
#RUN apt install -y python3-pip 
#RUN pip3 install --upgrade pip
#RUN python3.8 -m pip install fastapi
RUN pip3 install ffmpeg
RUN pip3 install opencv-python opencv-contrib-python
RUN pip3 install fastapi uvicorn imutils python-multipart

RUN python3.8 -m pip install fastapi uvicorn imutils python-multipart opencv-python opencv-contrib-python

#CMD [ "python3", "-m" , "flask", "run", "--host=0.0.0.0"]
EXPOSE 8001
#uvicorn.run("pysample:app", host="0.0.0.0", port=8001, log_level="info")
CMD [ "python3", "pysample.py"]

#docker build -f pysample.Dockerfile -t pysample .
#9002 public port
#8001 internal app docker port, defind in pysample.py
#docker run -d --restart always -it --rm -p 9002:8001 --name pysample_9002 pysample
