FROM python:3.7-buster
WORKDIR /app
COPY . .

#RUN apt-get update && apt-get install -y python3-opencv
RUN apt-get update
RUN apt-get install -y libgl1-mesa-dev
RUN apt-get install libsm6 libxext6  -y
RUN pip3 install ffmpeg
RUN pip3 install opencv-python
RUN pip3 install opencv-contrib-python

RUN pip3 install fastapi
RUN pip3 install uvicorn
RUN pip3 install imutils
RUN pip3 install python-multipart

#CMD [ "python3", "-m" , "flask", "run", "--host=0.0.0.0"]
CMD [ "python3", "pysample.py"]

#docker build -f pysample.Dockerfile -t pysample .
#9002 public port
#8001 internal app docker port, defind in pysample.py
#docker run -d --restart always -it --rm -p 9002:8001 --name pysample_9002 pysample
