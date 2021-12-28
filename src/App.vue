<template>
  <v-app>
    <v-app-bar
      app
      color="rgba(10, 175, 230, 1)"
      dark
    >
     <h3 class="text-center" style="width: 100%">Guaraci App</h3>
    </v-app-bar>

    <v-main>
      <router-view />
    </v-main>
  </v-app>
</template>

<script>
import router from "./router";
export default {
  name: 'App',

  data: () => ({
    //
  }),
  methods:{
    goToLogin(){
      router.push("/login");
    }
  }
};
</script>
