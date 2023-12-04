# Tool for changning HiSilicon/Goke encoder params.
To compile download and extract this repo, then change TPATH= and MPP= accordingly.
https://github.com/OpenIPC/silicon_research/tree/474850aefa7e0a141d85c91589caab3c68910787/sdk/gk7205v300/gmp

Sample usage:
gkrcparams --MaxQp 30 --MaxI 2

Tested on gk7205 and h3516
majestic must running when calling the app. Changes won't persist if majestic is restarted.

# ToDo:
Should be possible to link to OpenIPC repo downloaded via BuildRoot process.

