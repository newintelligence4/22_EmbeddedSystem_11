cmd_/home/vlsi-emb2022/working/asdf/Module.symvers := sed 's/\.ko$$/\.o/' /home/vlsi-emb2022/working/asdf/modules.order | scripts/mod/modpost -m -a  -o /home/vlsi-emb2022/working/asdf/Module.symvers -e -i Module.symvers   -T -