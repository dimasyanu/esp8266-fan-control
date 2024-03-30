<script setup>
</script>

<template>
  <ul class="p-0">
    <li v-for="i in 4" :class="{ active: checkActive(i) }" class="btn btn-light btn-circle btn-circle-xl m-1" @click="changeSpeed(i - 1)">
      <span v-if="!loading">{{ i - 1 }}</span>
      <i v-else class="bi bi-gear icon-rotating"></i>
    </li>
  </ul>
</template>

<script>
import axios from 'axios'
export default {
  data() {
    return {
      baseUrl: import.meta.env.VITE_BASE_URL,
      username: import.meta.env.VITE_USERNAME,
      password: import.meta.env.VITE_PASSWORD,
      speed: 0,
      reqSpeed: 0,
      loading: true
    }
  },
  methods: {
    checkActive(i) {
      return this.speed !== this.reqSpeed ? i - 1 === this.reqSpeed : i - 1 === this.reqSpeed
    },
    changeSpeed(reqSpeed) {
      if (this.loading) return

      this.reqSpeed = reqSpeed
      let data = {
        username: this.username,
        password: this.password,
        speed: reqSpeed
      }
      
      this.loading = true
      axios.post(this.baseUrl + '/', data, { headers: { 'content-type': 'application/x-www-form-urlencoded' } })
        .then(res => {
          if (typeof res.data.speed === 'string') {
            this.speed = parseInt(res.data.speed)
            return
          }
          this.speed = res.data.speed
        })
        .catch(err => {
          console.log(err)

        })
        .finally(() => {
          this.loading = false
          this.reqSpeed = this.speed
        })
    }
  },
  mounted() {
    this.loading = true
    axios.get(this.baseUrl + '/')
      .then(res => {
        if (typeof res.data.speed === 'string') {
          this.speed = parseInt(res.data.speed)
          return
        }
        this.speed = res.data.speed
      })
      .catch(err => {
        console.log(err)
      })
      .finally(() => {
        this.loading = false
          this.reqSpeed = this.speed
      })
  }
}
</script>
