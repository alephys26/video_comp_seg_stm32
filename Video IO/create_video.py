import cv2
import os
import glob
from argparse import ArgumentParser as ap

def create_video(args):

    codec = cv2.VideoWriter_fourcc(*"mp4v")

    image_files = sorted(glob.glob(os.path.join(args.input_dir, '*.png')))

    if len(image_files) == 0:
        print("No images found in the specified path.")
    else:
        first_image = cv2.imread(image_files[0])
        frame_height, frame_width, _ = first_image.shape

        video_writer = cv2.VideoWriter(args.out_dir+'masked_video.mp4', codec, 10, (frame_width, frame_height))

        for image_file in image_files:

            image = cv2.imread(image_file)

            video_writer.write(image)

        video_writer.release()

        print(f"Video created successfully and saved at {args.out_dir+'masked_video.mp4'}")
        
parser = ap()
parser.add_argument("input_dir",type=str)
parser.add_argument("out_dir",type=str)
args = parser.parse_args()

create_video(args)