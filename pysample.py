import uvicorn
import cv2
import base64
from fastapi import FastAPI, File, Form, UploadFile
import numpy
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel

class img2base64_response(BaseModel):
    ok: int
    data: str
    pass

app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

@app.post("/api/img2base64", response_model=img2base64_response)
async def api_img2base64(image: UploadFile = File(...)):
    try:

        # file: bytes = File(...), fileb: UploadFile = File(...), token: str = Form(...)
        #img = cv2.imdecode(numpy.fromstring(request.files['file'].read(), numpy.uint8), cv2.IMREAD_UNCHANGED)
        img = cv2.imdecode(numpy.frombuffer((await image.read()), numpy.uint8), cv2.IMREAD_UNCHANGED)

        encoded_img = base64.b64encode(img)

        return img2base64_response(
            ok=1,
            data=encoded_img
        )
    except Exception as ex:
        print(ex)
        return img2base64_response(
            ok=0,
            data=str(ex)
        )
    pass

@app.get("/")
async def root():
    return {"message": "api description URI: /docs"}    

# can move to other file

if __name__ == "__main__":
    uvicorn.run("pysample:app", host="0.0.0.0", port=8001, log_level="info")
