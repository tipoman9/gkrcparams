# Tool for changning HiSilicon/Goke encoder params.
To compile download and extract this repo, then change TPATH= and MPP= accordingly.
https://github.com/OpenIPC/silicon_research/tree/474850aefa7e0a141d85c91589caab3c68910787/sdk/gk7205v300/gmp

Sample usage:
gkrcparams --MaxQp 30 --MaxI 2

Tested on gk7205 and h3516
majestic must running when calling the app. Changes won't persist if majestic is restarted.


Current options that can be changed
 --MaxI     u32MaxIprop[u32MinIprop,100]   
 --MinI     u32MinIprop[1,u32MaxIprop]    
 --MaxQp    u32MaxQp[MinQp, 51]  
 --MinQp    u32MinQp[0, 51]   
 --MaxReEnc s32MaxReEncodeTimes[0, 3]     
 --MaxQpD   u32MaxQpDelta[0, 4]   
 --RefreshNum u32RefreshNum (enables IntraRefresh)  
 --help      Display this help 
	  
	  
- u32MaxIprop 
Maximum ratio of bits allocated to the I-frames and P-frames
Value range: [u32MinIprop,100]
Default value: 100

-u32MaxQp 
Maximum QP value of the P-frame and B-frame
Value range: [MinQp, 51]
Default value: 51

-u32MinQp 
Minimum QP value of the P-frame and B-frame
Value range: [0, 51]
Default value: 16

- s32MaxReEncodeTimes 
Number of times that each frame is re-encoded. The value 0
indicates that the frame is not re-encoded.
Value range: [0, 3]
Default value: 2
	  
− u32MaxQpDelta
Indicates the difference between the maximum QP value of the frame level and the
maximum QP value of the CU level. This is an advanced CVBR parameter. When the
image content is complex, the bit rate control increases the QP value. When the
frame-level QP value is adjusted to the maximum, the bit rate control does not
increase the frame-level QP value. However, the CU/MB-level bit rate control still
takes effect, and the QP value in the strong texture area of the image can be increased.


SDK and param details here:
http://fabemo.ru/pcb/ReleaseDoc_v01/zh/01.software/board/HiMPP%20V4.0%20%E5%AA%92%E4%BD%93%E5%A4%84%E7%90%86%E8%BD%AF%E4%BB%B6%E5%BC%80%E5%8F%91%E5%8F%82%E8%80%83.pdf

# ToDo:
Should be possible to link to OpenIPC repo downloaded via BuildRoot process.

