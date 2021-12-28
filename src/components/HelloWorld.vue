<template>
  <v-container>
    <v-row class="text-center" no-gutters>
      <v-col cols="12">
        <v-img v-if="openCurtain"
          :src="require('../assets/openCurtain.png')"
          class="my-3"
          contain
          height="200"
        />
        <v-img v-else
          :src="require('../assets/closedCurtain.png')"
          class="my-3"
          contain
          height="200"
        />
      </v-col>
     
      <v-col cols="6" align-self="center" justify="center" class="text-center">
        <p class="text-center mt-4">
          Abrir sua cortina: 
        </p>
      </v-col>
      <v-col cols="6">
        <v-switch
        class="text-center"
          v-model="openCurtain"
          color="primary"
        ></v-switch>
      </v-col>
      <v-col cols="12"  >
        <div id="clock">
          <p class="text">Seu horário atual</p>
          <p class="time mb-0">{{ clock.time }}</p>
          <p class="date">{{ clock.date }}</p>
        </div>
      </v-col>
      <v-col cols="12" class="mb-6">
        <h3 class="mt-7 mb-3">Qual horário pretende se acordar amanhã?</h3>
        <vue-clock-picker done-text="Confirmar"  cancel-text="Cancelar" active-color="rgba(10, 175, 230, 1)" @timeset="closeClockPicker" id="clockPicker" v-model="valueClockPicker" placeholder="Defina seu horário" input-class="width:300px!important"></vue-clock-picker>
      </v-col>

      <v-dialog
      v-model="dialog"
      persistent
      max-width="290"
    >
      <v-card>
        <v-card-title class="text-h5">
          Cortina Programada
        </v-card-title>
        <v-card-text>Sua cortina está configurada para abrir às {{valueClockPicker}} horas. Tenha um ótimo sonho.</v-card-text>
        <v-card-text  v-if="openCurtain">Sua cortina está aberta deseja fechá-la?.</v-card-text>
         <v-card-actions v-if="openCurtain">
          <v-spacer></v-spacer>
          <v-btn
            color="green darken-1"
            text
            @click="dialog = false; openCurtain = false "
          >
            Sim
          </v-btn>
          <v-btn
            color="green darken-1"
            text
            @click="dialog = false"
          >
            Não
          </v-btn>
        </v-card-actions>
        <v-card-actions v-else>
          <v-spacer></v-spacer>
          <v-btn
            color="green darken-1"
            text
            @click="dialog = false"
          >
            Entendi
          </v-btn>
        </v-card-actions>
      </v-card>
    </v-dialog>
      
    </v-row>
  </v-container>
</template>

<script>
import VueClockPicker from '@pencilpix/vue2-clock-picker';
import '@pencilpix/vue2-clock-picker/dist/vue2-clock-picker.min.css';
import axios from 'axios'
export default {
  name: 'Home',
  components: {
    VueClockPicker,
  },
  data: () => ({
    openCurtain: false, 
    valueClockPicker: null,
    week: ['Domingo','Segunda', 'Terça', 'Quarta', 'Quinta', 'Sexta', 'Sábado'],
    clock: {
        time: '',
        date: ''
    },
    dialog: false
    }),
  methods: {
    closeClockPicker(){
      this.dialog = true
    },
    zeroPadding(num, digit) {
      var zero = '';
      for(var i = 0; i < digit; i++) {
          zero += '0';
      }
      return (zero + num).slice(-digit);
    },
    updateTime() {
      var cd = new Date();
      this.clock.time = this.zeroPadding(cd.getHours(), 2) + ':' + this.zeroPadding(cd.getMinutes(), 2) + ':' + this.zeroPadding(cd.getSeconds(), 2);
      this.clock.date = this.zeroPadding(cd.getFullYear(), 4) + '-' + this.zeroPadding(cd.getMonth()+1, 2) + '-' + this.zeroPadding(cd.getDate(), 2) + ' ' + this.week[cd.getDay()];
    }
  },
  async created(){
    
    this.updateTime();
    setInterval(this.updateTime, 1000);
  },
  watch: {
    openCurtain: async function  (date) {
      console.log('mudou')
      console.log(date);
      let operation = 'close'
      if(date){
        operation='open'
      }
    
      const {data} = await axios.post(`http://192.168.1.197/${operation}`)
      console.log(data);
    }
  }
}
</script>
<style>
#clockPicker{
  background-color: rgba(10, 175, 230, 1);
  width: 50%;
}
#clock {
    font-family: 'Share Tech Mono', monospace;
    background: rgba(10, 175, 230, 1);
    text-align: center;
    color: #daf6ff;
    text-shadow: 0 0 20px rgba(10, 175, 230, 1),  0 0 20px rgba(10, 175, 230, 0);
}
.time {
    letter-spacing: 0.05em;
    font-size: 40px;
    padding: 5px 0;
    margin-bottom: 3px;
}
.date {
    letter-spacing: 0.1em;
    font-size: 12px;
}
.text {
    letter-spacing: 0.1em;
    font-size: 14px;
    margin-bottom: 0 !important;
}

</style>
